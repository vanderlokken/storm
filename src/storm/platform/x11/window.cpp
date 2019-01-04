#include <storm/window.h>

#include <iostream>

#include <array>
#include <algorithm>
#include <climits>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <X11/extensions/Xfixes.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/proxy_window_observer.h>
#include <storm/rectangle.h>

namespace storm {

namespace {

template <class T, class... Args>
void runCallback( const std::function<T> &callback, Args&&... args ) {
    if( callback ) {
        callback( std::forward<Args>(args)... );
    }
}

class PointerLockingRegion {
public:
    PointerLockingRegion(
            ::Display *display, ::Window window, Rectangle area ) :
        _display( display )
    {
        std::array<int, 1> devices = { XIAllDevices };

        _left = XFixesCreatePointerBarrier(
            _display,
            window,
            area.x,
            area.y,
            area.x,
            area.getBottom(),
            BarrierNegativeX,
            devices.size(),
            devices.data() );

        _right = XFixesCreatePointerBarrier(
            _display,
            window,
            area.getRight(),
            area.y,
            area.getRight(),
            area.getBottom(),
            BarrierPositiveX,
            devices.size(),
            devices.data() );

        _top = XFixesCreatePointerBarrier(
            _display,
            window,
            area.x,
            area.y,
            area.getRight(),
            area.y,
            BarrierNegativeY,
            devices.size(),
            devices.data() );

        _bottom = XFixesCreatePointerBarrier(
            _display,
            window,
            area.x,
            area.getBottom(),
            area.getRight(),
            area.getBottom(),
            BarrierPositiveY,
            devices.size(),
            devices.data() );
    }

    PointerLockingRegion(
        const PointerLockingRegion& ) = delete;
    PointerLockingRegion& operator = (
        const PointerLockingRegion& ) = delete;

    ~PointerLockingRegion() {
        XFixesDestroyPointerBarrier( _display, _left );
        XFixesDestroyPointerBarrier( _display, _right );
        XFixesDestroyPointerBarrier( _display, _top );
        XFixesDestroyPointerBarrier( _display, _bottom );
    }

private:
    Display *_display;

    PointerBarrier _left   = 0;
    PointerBarrier _right  = 0;
    PointerBarrier _top    = 0;
    PointerBarrier _bottom = 0;
};

class WindowImplementation : public Window {
// private:
//     static constexpr long eventMask =
//         FocusChangeMask |
//         KeyPressMask |
//         KeyReleaseMask;

public:
    WindowImplementation() {
        _eventHandlers = {
            {XI_FocusIn, &WindowImplementation::onFocusIn},
            {XI_FocusOut, &WindowImplementation::onFocusOut}
        };

        loadAtoms();
        queryRequiredExtensions();
        createTransparentCursor();

        Screen *screen = XDefaultScreenOfDisplay( _display );

        _handle = XCreateSimpleWindow(
            _display,
            XDefaultRootWindow(_display), // parent
            0,                            // x
            0,                            // y
            1,                            // width
            1,                            // height
            0,                            // border width
            XBlackPixelOfScreen(screen),  // border color
            XBlackPixelOfScreen(screen)   // background color
        );

        // XSelectInput( _display, _handle, eventMask );

        std::array<Atom, 1> protocols = { _atoms.wmDeleteWindow };
        XSetWMProtocols(
            _display,
            _handle,
            protocols.data(),
            protocols.size() );

        removeDecorations();
        setWindowedFullscreenMode();
        selectInputEvents();
    }

    ~WindowImplementation() {
        XDestroyWindow( _display, _handle );
        XFreeCursor( _display, _transparentCursor );
    }

    void processEvents() override {
        XEvent event;

        // TODO: XFilterEvent?

        while( XCheckTypedEvent(
                _display, GenericEvent, &event) ) {
            if( event.xcookie.extension == _xinputOpcode ) {
                const auto iterator =
                    _eventHandlers.find( event.xcookie.evtype );

                if( iterator != _eventHandlers.end() ) {
                    XGetEventData( _display, &event.xcookie );

                    const auto handler = iterator->second;
                    (this->*handler)( event.xcookie.data );

                    std::cout << "got ev.\n";

                    XFreeEventData( _display, &event.xcookie );
                }
            }
        }

        while( XCheckTypedWindowEvent(
                _display, _handle, ClientMessage, &event) ) {
            if( static_cast<Atom>(event.xclient.data.l[0]) ==
                    _atoms.wmDeleteWindow ) {
                runCallback( _proxyObserver->onShutdownRequested );
            }
        }
    }

    void addObserver( std::weak_ptr<WindowObserver> observer ) override {
        _proxyObserver.addObserver( std::move(observer) );
    }

    void* getHandle() const override {
        return reinterpret_cast<void*>( _handle );
    }

    Dimensions getDimensions() const override {
        return _dimensions;
    }

    void setWindowedFullscreenMode() override {
        setFullscreenModeEnabled( true );

        Screen *screen = XDefaultScreenOfDisplay( _display );

        _dimensions = Dimensions(
            XWidthOfScreen(screen),
            XHeightOfScreen(screen)
        );
    }

    void setWindowedMode( Dimensions dimensions ) override {
        setFullscreenModeEnabled( false );

        Screen *screen = XDefaultScreenOfDisplay( _display );

        XMoveResizeWindow(
            _display,
            _handle,
            (XWidthOfScreen(screen) - static_cast<int>(dimensions.width)) / 2,
            (XHeightOfScreen(screen) - static_cast<int>(dimensions.height)) / 2,
            dimensions.width,
            dimensions.height );

        _dimensions = dimensions;
    }

    bool isVisible() const override {
        XWindowAttributes windowAttributes;
        XGetWindowAttributes( _display, _handle, &windowAttributes );
        return windowAttributes.map_state == IsViewable;
    }

    void setVisible( bool visible ) override {
        if( visible ) {
            XMapWindow( _display, _handle );
        } else {
            XUnmapWindow( _display, _handle );
        }
    }

    bool hasFocus() const override {
        ::Window activeWindow = None;
        int focusState = 0;

        XGetInputFocus( _display, &activeWindow, &focusState );
        return activeWindow == _handle;
    }

    std::string_view getTitle() const override {
        return _title;
    }

    void setTitle( std::string title ) override {
        _title = std::move( title );

        std::vector<unsigned char> buffer( _title.size() );

        std::copy(
            _title.begin(),
            _title.end(),
            buffer.begin() );

        XChangeProperty(
            _display,
            _handle,
            _atoms.netWmName,
            _atoms.utf8String,
            CHAR_BIT /* format, bits */,
            PropModeReplace,
            buffer.data(),
            buffer.size() );
    }

    bool isPointerVisible() const override {
        return _isPointerVisible;
    }

    void setPointerVisible( bool visible ) override {
        _isPointerVisible = visible;

        if( _isPointerVisible ) {
            XUndefineCursor( _display, _handle );
        } else {
            XDefineCursor( _display, _handle, _transparentCursor );
        }
    }

    bool isPointerLocked() const override {
        return _isPointerLocked;
    }

    void setPointerLocked( bool locked ) override {
        _isPointerLocked = locked;

        if( hasFocus() ) {
            if( !_isPointerLocked ) {
                _pointerLockingRegion.reset();
            } else {
                _pointerLockingRegion.emplace( _display, _handle, Rectangle() );
            }
        }
    }

private:
    void loadAtoms() {
        auto load = [this]( std::string_view name ) {
            return XInternAtom(
                _display, name.data(), /*onlyExisting = */ false );
        };

        _atoms.atom                 = load( "ATOM" );
        _atoms.motifWmHints         = load( "_MOTIF_WM_HINTS" );
        _atoms.netWmName            = load( "_NET_WM_NAME" );
        _atoms.netWmState           = load( "_NET_WM_STATE" );
        _atoms.netWmStateFullscreen = load( "_NET_WM_STATE_FULLSCREEN" );
        _atoms.utf8String           = load( "UTF8_STRING" );
        _atoms.wmDeleteWindow       = load( "WM_DELETE_WINDOW" );
    }

    void queryRequiredExtensions() {
        const char *missingXinputMessage =
            "The display server doesn't support version 2.0 of the "
            "'XInput' extension";
        const char *missingXfixesMessage =
            "The display server doesn't support version 5.0 of the "
            "'XFixes' extension";

        int firstEventCode = 0;
        int firstErrorCode = 0;

        if( !XQueryExtension(
                _display,
                "XInputExtension",
                &_xinputOpcode,
                &firstEventCode,
                &firstErrorCode) ) {
            throw SystemRequirementsNotMet() << missingXinputMessage;
        }

        if( !XFixesQueryVersion(
                _display,
                &firstEventCode,
                &firstErrorCode) ) {
            throw SystemRequirementsNotMet() << missingXfixesMessage;
        }

        int majorVersion = 2;
        int minorVersion = 0;

        if( XIQueryVersion(
                _display, &majorVersion, &minorVersion) == BadRequest ) {
            throw SystemRequirementsNotMet() << missingXinputMessage;
        }

        majorVersion = 5;
        minorVersion = 0;

        XFixesQueryVersion( _display, &majorVersion, &minorVersion );

        if( majorVersion < 5 ) {
            throw SystemRequirementsNotMet() << missingXfixesMessage;
        }
    }

    void createTransparentCursor() {
        const char transparentPixel = 0;

        Pixmap pixmap = XCreateBitmapFromData(
            _display,
            XDefaultRootWindow(_display),
            &transparentPixel,
            1, // width
            1  // height
        );

        XColor black = {};

        _transparentCursor = XCreatePixmapCursor(
            _display,
            pixmap,
            pixmap,
            &black,
            &black,
            0,
            0 );

        XFreePixmap( _display, pixmap );
    }

    void removeDecorations() const {
        // Note: see the 'Xm/MwmUtil.h' header file from the 'libmotif-dev'
        // package
        std::array<uint32_t, 5> hints = {2, 0, 0, 0, 0};

        XChangeProperty(
            _display,
            _handle,
            _atoms.motifWmHints,
            _atoms.motifWmHints,
            sizeof(int32_t) * CHAR_BIT /* format, bits */,
            PropModeReplace,
            reinterpret_cast<unsigned char*>(hints.data()),
            hints.size() );
    }

    void setFullscreenModeEnabled( bool enabled ) const {
        XClientMessageEvent event = {};

        event.type = ClientMessage;
        event.window = _handle;
        event.message_type = _atoms.netWmState;
        event.format = 32;
        event.data.l[0] = enabled ? 1 : 0;
        event.data.l[1] = _atoms.netWmStateFullscreen;
        event.data.l[2] = None;
        event.data.l[3] = 1; // source indication, which means "normal app."
        event.data.l[4] = 0;

        XSendEvent(
            _display,
            XDefaultRootWindow(_display),
            False,
            SubstructureRedirectMask | SubstructureNotifyMask,
            reinterpret_cast<XEvent*>(&event) );
    }

    void selectInputEvents() const {
        unsigned char mask[4] = {};

        XISetMask( mask, XI_ButtonPress );
        XISetMask( mask, XI_ButtonRelease );
        XISetMask( mask, XI_FocusIn );
        XISetMask( mask, XI_FocusOut );
        XISetMask( mask, XI_KeyPress );
        XISetMask( mask, XI_KeyRelease );
        XISetMask( mask, XI_Motion );

        XIEventMask eventMask;
        eventMask.deviceid = XIAllDevices;
        eventMask.mask_len = sizeof( mask );
        eventMask.mask = mask;

        XISelectEvents( _display, _handle, &eventMask, 1 );
    }

    void onFocusIn( const void* ) {
        runCallback( _proxyObserver->onFocusReceived );
    }

    void onFocusOut( const void* ) {
        // std::cout << event.xfocus.mode << std::endl;
        // std::cout << event.xfocus.detail << std::endl;
        runCallback( _proxyObserver->onFocusLost );
    }

    using EventHandlers =
        std::unordered_map<int, void(WindowImplementation::*)(const void*)>;
    EventHandlers _eventHandlers;

    DisplayConnection _display;
    ::Window _handle;

    int _xinputOpcode = 0;

    Cursor _transparentCursor;

    struct {
        Atom atom;
        Atom motifWmHints;
        Atom netWmName;
        Atom netWmState;
        Atom netWmStateFullscreen;
        Atom utf8String;
        Atom wmDeleteWindow;
    } _atoms;

    ProxyWindowObserver _proxyObserver;

    std::string _title;
    Dimensions _dimensions;

    bool _isPointerVisible = true;
    bool _isPointerLocked = false;

    std::optional<PointerLockingRegion> _pointerLockingRegion;
};

} // namespace

Window::Pointer Window::create() {
    return std::make_shared<WindowImplementation>();
}

}
