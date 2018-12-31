#include <storm/window.h>

#include <array>
#include <algorithm>
#include <climits>
#include <string_view>
#include <vector>

#include <X11/extensions/Xfixes.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/proxy_window_observer.h>

namespace storm {

namespace {

template <class T, class... Args>
void runCallback( const std::function<T> &callback, Args&&... args ) {
    if( callback ) {
        callback( std::forward<Args>(args)... );
    }
}

class WindowImplementation : public Window {
private:
    static constexpr long eventMask =
        XI_ButtonPressMask |
        XI_ButtonReleaseMask |
        XI_FocusInMask |
        XI_FocusOutMask |
        XI_KeyPressMask |
        XI_KeyReleaseMask |
        XI_EnterMask |
        XI_LeaveMask |
        XI_MotionMask;

public:
    WindowImplementation() {
        loadAtoms();

        Screen *screen = XDefaultScreenOfDisplay( _display );

        const ::Window parentWindow = XDefaultRootWindow( _display );

        const unsigned long borderColor = XBlackPixelOfScreen( screen );
        const unsigned long backgroundColor = XWhitePixelOfScreen( screen );

        _handle = XCreateSimpleWindow(
            _display,
            parentWindow,
            0, // x
            0, // y
            1, // width
            1, // height
            0, // border width
            borderColor,
            backgroundColor );

        XSelectInput( _display, _handle, eventMask );

        std::array<Atom, 1> protocols = { _atoms.wmDeleteWindow };
        XSetWMProtocols(
            _display,
            _handle,
            protocols.data(),
            protocols.size() );

        removeDecorations();

        setWindowedFullscreenMode();
    }

    ~WindowImplementation() {
        XDestroyWindow( _display, _handle );
    }

    void processEvents() override {
        XEvent event;

        while( XCheckWindowEvent(_display, _handle, eventMask, &event) ) {
            if( XFilterEvent(&event, _handle) ) {
                continue;
            }
            // TODO: handle
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
            XFixesShowCursor( _display, _handle );
        } else {
            XFixesHideCursor( _display, _handle );
        }
    }

    bool isPointerLocked() const override {
        return _isPointerLocked;
    }

    void setPointerLocked( bool locked ) override {
        _isPointerLocked = locked;
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

    void removeDecorations() const {
        // Note: see the 'Xm/MwmUtil.h' header file from the 'libmotif-dev'
        // package
        std::array<uint32_t, 5> hints = {3, 0, 0, 0, 0};

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

    DisplayConnection _display;
    ::Window _handle;

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
};

} // namespace

Window::Pointer Window::create() {
    return std::make_shared<WindowImplementation>();
}

}
