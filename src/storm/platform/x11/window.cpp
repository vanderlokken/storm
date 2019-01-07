#include <storm/window.h>

#include <algorithm>
#include <array>
#include <climits>
#include <optional>
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

// The following mapping was obtained from the 'xmodmap -pke' command output.
constexpr std::array<std::optional<KeyboardKey>, 136> keycodeMapping = {
    /*   0 */ std::nullopt,
    /*   1 */ std::nullopt,
    /*   2 */ std::nullopt,
    /*   3 */ std::nullopt,
    /*   4 */ std::nullopt,
    /*   5 */ std::nullopt,
    /*   6 */ std::nullopt,
    /*   7 */ std::nullopt,
    /*   8 */ std::nullopt,
    /*   9 */ KeyboardKey::Escape,
    /*  10 */ KeyboardKey::Digit1,
    /*  11 */ KeyboardKey::Digit2,
    /*  12 */ KeyboardKey::Digit3,
    /*  13 */ KeyboardKey::Digit4,
    /*  14 */ KeyboardKey::Digit5,
    /*  15 */ KeyboardKey::Digit6,
    /*  16 */ KeyboardKey::Digit7,
    /*  17 */ KeyboardKey::Digit8,
    /*  18 */ KeyboardKey::Digit9,
    /*  19 */ KeyboardKey::Digit0,
    /*  20 */ KeyboardKey::Minus,
    /*  21 */ KeyboardKey::Equals,
    /*  22 */ KeyboardKey::Backspace,
    /*  23 */ KeyboardKey::Tab,
    /*  24 */ KeyboardKey::Q,
    /*  25 */ KeyboardKey::W,
    /*  26 */ KeyboardKey::E,
    /*  27 */ KeyboardKey::R,
    /*  28 */ KeyboardKey::T,
    /*  29 */ KeyboardKey::Y,
    /*  30 */ KeyboardKey::U,
    /*  31 */ KeyboardKey::I,
    /*  32 */ KeyboardKey::O,
    /*  33 */ KeyboardKey::P,
    /*  34 */ KeyboardKey::LeftBracket,
    /*  35 */ KeyboardKey::RightBracket,
    /*  36 */ KeyboardKey::Enter,
    /*  37 */ KeyboardKey::LeftControl,
    /*  38 */ KeyboardKey::A,
    /*  39 */ KeyboardKey::S,
    /*  40 */ KeyboardKey::D,
    /*  41 */ KeyboardKey::F,
    /*  42 */ KeyboardKey::G,
    /*  43 */ KeyboardKey::H,
    /*  44 */ KeyboardKey::J,
    /*  45 */ KeyboardKey::K,
    /*  46 */ KeyboardKey::L,
    /*  47 */ KeyboardKey::Semicolon,
    /*  48 */ KeyboardKey::Apostrophe,
    /*  49 */ KeyboardKey::GraveAccent,
    /*  50 */ KeyboardKey::LeftShift,
    /*  51 */ KeyboardKey::Backslash,
    /*  52 */ KeyboardKey::Z,
    /*  53 */ KeyboardKey::X,
    /*  54 */ KeyboardKey::C,
    /*  55 */ KeyboardKey::V,
    /*  56 */ KeyboardKey::B,
    /*  57 */ KeyboardKey::N,
    /*  58 */ KeyboardKey::M,
    /*  59 */ KeyboardKey::Comma,
    /*  60 */ KeyboardKey::Period,
    /*  61 */ KeyboardKey::Slash,
    /*  62 */ KeyboardKey::RightShift,
    /*  63 */ KeyboardKey::KeypadAsterisk,
    /*  64 */ KeyboardKey::LeftAlter,
    /*  65 */ KeyboardKey::Space,
    /*  66 */ KeyboardKey::CapsLock,
    /*  67 */ KeyboardKey::F1,
    /*  68 */ KeyboardKey::F2,
    /*  69 */ KeyboardKey::F3,
    /*  70 */ KeyboardKey::F4,
    /*  71 */ KeyboardKey::F5,
    /*  72 */ KeyboardKey::F6,
    /*  73 */ KeyboardKey::F7,
    /*  74 */ KeyboardKey::F8,
    /*  75 */ KeyboardKey::F9,
    /*  76 */ KeyboardKey::F10,
    /*  77 */ KeyboardKey::NumLock,
    /*  78 */ KeyboardKey::ScrollLock,
    /*  79 */ KeyboardKey::Keypad7,
    /*  80 */ KeyboardKey::Keypad8,
    /*  81 */ KeyboardKey::Keypad9,
    /*  82 */ KeyboardKey::KeypadMinus,
    /*  83 */ KeyboardKey::Keypad4,
    /*  84 */ KeyboardKey::Keypad5,
    /*  85 */ KeyboardKey::Keypad6,
    /*  86 */ KeyboardKey::KeypadPlus,
    /*  87 */ KeyboardKey::Keypad1,
    /*  88 */ KeyboardKey::Keypad2,
    /*  89 */ KeyboardKey::Keypad3,
    /*  90 */ KeyboardKey::Keypad0,
    /*  91 */ KeyboardKey::KeypadDelete,
    /*  92 */ std::nullopt,
    /*  93 */ std::nullopt,
    /*  94 */ std::nullopt,
    /*  95 */ KeyboardKey::F11,
    /*  96 */ KeyboardKey::F12,
    /*  97 */ std::nullopt,
    /*  98 */ std::nullopt,
    /*  99 */ std::nullopt,
    /* 100 */ std::nullopt,
    /* 101 */ std::nullopt,
    /* 102 */ std::nullopt,
    /* 103 */ std::nullopt,
    /* 104 */ KeyboardKey::KeypadEnter,
    /* 105 */ KeyboardKey::RightControl,
    /* 106 */ KeyboardKey::KeypadSlash,
    /* 107 */ KeyboardKey::PrintScreen,
    /* 108 */ KeyboardKey::RightAlter,
    /* 109 */ std::nullopt,
    /* 110 */ KeyboardKey::Home,
    /* 111 */ KeyboardKey::Up,
    /* 112 */ KeyboardKey::PageUp,
    /* 113 */ KeyboardKey::Left,
    /* 114 */ KeyboardKey::Right,
    /* 115 */ KeyboardKey::End,
    /* 116 */ KeyboardKey::Down,
    /* 117 */ KeyboardKey::PageDown,
    /* 118 */ KeyboardKey::Insert,
    /* 119 */ KeyboardKey::Delete,
    /* 120 */ std::nullopt,
    /* 121 */ std::nullopt,
    /* 122 */ std::nullopt,
    /* 123 */ std::nullopt,
    /* 124 */ std::nullopt,
    /* 125 */ std::nullopt,
    /* 126 */ std::nullopt,
    /* 127 */ KeyboardKey::Pause,
    /* 128 */ std::nullopt,
    /* 129 */ std::nullopt,
    /* 130 */ std::nullopt,
    /* 131 */ std::nullopt,
    /* 132 */ std::nullopt,
    /* 133 */ KeyboardKey::LeftCommand,
    /* 134 */ KeyboardKey::RightCommand,
    /* 135 */ KeyboardKey::Menu
};

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
        // The following code uses the 'INT_MIN' and 'INT_MAX' constants instead
        // of making an exact bounding box due to the following bug in X.Org
        // Server: https://gitlab.freedesktop.org/xorg/xserver/issues/606

        _left = XFixesCreatePointerBarrier(
            _display,
            window,
            area.x,
            INT_MIN,
            area.x,
            INT_MAX,
            BarrierPositiveX,
            0,
            nullptr );

        _right = XFixesCreatePointerBarrier(
            _display,
            window,
            area.getRight(),
            INT_MIN,
            area.getRight(),
            INT_MAX,
            BarrierNegativeX,
            0,
            nullptr );

        _top = XFixesCreatePointerBarrier(
            _display,
            window,
            INT_MIN,
            area.y,
            INT_MAX,
            area.y,
            BarrierPositiveY,
            0,
            nullptr );

        _bottom = XFixesCreatePointerBarrier(
            _display,
            window,
            INT_MIN,
            area.getBottom(),
            INT_MAX,
            area.getBottom(),
            BarrierNegativeY,
            0,
            nullptr );
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
    ::Display *_display;

    PointerBarrier _left   = 0;
    PointerBarrier _right  = 0;
    PointerBarrier _top    = 0;
    PointerBarrier _bottom = 0;
};

// This function allows to distinguish between mouse motion events and mouse
// wheel rotation events.
bool isMouseMotion( const XIValuatorState &valuatorState ) {
    return valuatorState.mask_len > 2 &&
        XIMaskIsSet( valuatorState.mask, 0 ) &&
        XIMaskIsSet( valuatorState.mask, 1 );
}

class WindowImplementation : public Window {
public:
    WindowImplementation() {
        _eventHandlers = {
            {XI_ButtonPress, &WindowImplementation::onButtonPress},
            {XI_ButtonRelease, &WindowImplementation::onButtonRelease},
            {XI_FocusIn, &WindowImplementation::onFocusIn},
            {XI_FocusOut, &WindowImplementation::onFocusOut},
            {XI_KeyPress, &WindowImplementation::onKeyPress},
            {XI_KeyRelease, &WindowImplementation::onKeyRelease},
            {XI_Motion, &WindowImplementation::onMotion},
            {XI_RawMotion, &WindowImplementation::onRawMotion}
        };

        loadAtoms();
        queryRequiredExtensions();
        createTransparentCursor();

        Screen *screen = XDefaultScreenOfDisplay( _display );

        _dimensions.width = XWidthOfScreen( screen );
        _dimensions.height = XHeightOfScreen( screen );

        _handle = XCreateSimpleWindow(
            _display,
            XDefaultRootWindow(_display), // parent
            0,                            // x
            0,                            // y
            _dimensions.width,            // width
            _dimensions.height,           // height
            0,                            // border width
            XBlackPixelOfScreen(screen),  // border color
            XBlackPixelOfScreen(screen)   // background color
        );

        XSelectInput( _display, _handle, StructureNotifyMask );

        selectXinputEvents(
            _handle,
            {
                XI_ButtonPress,
                XI_ButtonRelease,
                XI_FocusIn,
                XI_FocusOut,
                XI_KeyPress,
                XI_KeyRelease,
                XI_Motion
            });

        selectXinputEvents(
            XDefaultRootWindow(_display),
            {
                XI_RawMotion
            });

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
        XFreeCursor( _display, _transparentCursor );
    }

    void processEvents() override {
        XEvent event;

        for( int index = 0; index < XPending(_display); ++index ) {
            XNextEvent( _display, &event );

            if( XFilterEvent(&event, _handle) ) {
                continue;
            }

            if( event.type == GenericEvent &&
                    event.xcookie.extension == _xinputOpcode ) {
                const auto iterator =
                    _eventHandlers.find( event.xcookie.evtype );

                if( iterator != _eventHandlers.end() ) {
                    XGetEventData( _display, &event.xcookie );

                    const auto handler = iterator->second;
                    (this->*handler)( event.xcookie.data );

                    XFreeEventData( _display, &event.xcookie );
                }
            }

            if( event.type == ConfigureNotify ) {
                updateDimensions(
                    Dimensions(
                        static_cast<unsigned>(event.xconfigure.width),
                        static_cast<unsigned>(event.xconfigure.height)) );

                updatePointerLockingRegion();
            }

            if( event.type == ClientMessage &&
                    event.xclient.window == _handle &&
                    event.xclient.data.l[0] ==
                        static_cast<long>(_atoms.wmDeleteWindow) ) {
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

        updateDimensions(
            Dimensions(
                XWidthOfScreen(screen),
                XHeightOfScreen(screen)) );
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

        updateDimensions( dimensions );
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

        updatePointerLockingRegion();
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

    void selectXinputEvents(
        ::Window window, std::initializer_list<unsigned> events ) const
    {
        unsigned char mask[4] = {};

        for( unsigned event : events ) {
            XISetMask( mask, event );
        }

        XIEventMask eventMask;
        eventMask.deviceid = XIAllMasterDevices;
        eventMask.mask_len = sizeof( mask );
        eventMask.mask = mask;

        XISelectEvents( _display, window, &eventMask, 1 );
    }

    void onButtonPress( const void *data ) {
        onButtonStateChanged( data, /* pressed */ true );
    }

    void onButtonRelease( const void *data ) {
        onButtonStateChanged( data, /* pressed */ false );
    }

    void onFocusIn( const void* ) {
        runCallback( _proxyObserver->onFocusReceived );

        updatePointerLockingRegion();
    }

    void onFocusOut( const void* ) {
        runCallback( _proxyObserver->onFocusLost );

        _pointerLockingRegion.reset();
    }

    void onKeyPress( const void *data ) {
        onKeyStateChanged( data, /* pressed */ true );
    }

    void onKeyRelease( const void *data ) {
        onKeyStateChanged( data, /* pressed */ false );
    }

    void onMotion( const void *data ) {
        const XIDeviceEvent *event =
            reinterpret_cast<const XIDeviceEvent*>( data );

        if( isMouseMotion(event->valuators) ) {
            runCallback(
                _proxyObserver->onPointerMotion,
                IntVector2d(
                    static_cast<int>(event->event_x),
                    static_cast<int>(event->event_y)) );
        }
    }

    void onRawMotion( const void *data ) {
        const XIRawEvent *event =
            reinterpret_cast<const XIRawEvent*>( data );

        if( hasFocus() && isMouseMotion(event->valuators) ) {
            runCallback(
                _proxyObserver->onMouseMotion,
                IntVector2d(
                    static_cast<int>(event->raw_values[0]),
                    static_cast<int>(event->raw_values[1])) );
        }
    }

    void onButtonStateChanged( const void *data, bool pressed ) {
        const XIDeviceEvent *event =
            reinterpret_cast<const XIDeviceEvent*>( data );

        const std::array<std::optional<MouseButton>, 10> buttons = {
            std::nullopt,
            MouseButton::Left,
            MouseButton::Middle,
            MouseButton::Right,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            MouseButton::SideFirst,
            MouseButton::SideSecond
        };

        const size_t buttonIndex = event->detail;

        if( buttonIndex < buttons.size() && buttons[buttonIndex] ) {
            const MouseButton button = *buttons[buttonIndex];

            if( pressed ) {
                runCallback( _proxyObserver->onMouseButtonPressed, button );
            } else {
                runCallback( _proxyObserver->onMouseButtonReleased, button );
            }
        } else if( pressed ) {
            if( buttonIndex == 4 ) {
                runCallback( _proxyObserver->onMouseWheelRotated, -1.0 );
            }
            if( buttonIndex == 5 ) {
                runCallback( _proxyObserver->onMouseWheelRotated, 1.0 );
            }
        }
    }

    void onKeyStateChanged( const void *data, bool pressed ) {
        const XIDeviceEvent *event =
            reinterpret_cast<const XIDeviceEvent*>( data );

        const size_t keycode = event->detail;

        if( keycode < keycodeMapping.size() ) {
            if( const std::optional<KeyboardKey> &key =
                    keycodeMapping[keycode] ) {
                if( pressed ) {
                    if( event->flags & XIKeyRepeat ) {
                        runCallback(
                            _proxyObserver->onKeyboardKeyRepeated, *key );
                    } else {
                        runCallback(
                            _proxyObserver->onKeyboardKeyPressed, *key );
                    }
                } else {
                    runCallback( _proxyObserver->onKeyboardKeyReleased, *key );
                }
            }
        }
    }

    void updateDimensions( Dimensions dimensions ) {
        if( dimensions.width != _dimensions.width ||
            dimensions.height != _dimensions.height )
        {
            _dimensions = dimensions;
            runCallback( _proxyObserver->onResized );
        }
    }

    void updatePointerLockingRegion() {
        if( hasFocus() ) {
            if( !_isPointerLocked ) {
                _pointerLockingRegion.reset();
            } else {
                XWindowAttributes windowAttributes;
                XGetWindowAttributes( _display, _handle, &windowAttributes );

                _pointerLockingRegion.emplace(
                    _display,
                    _handle,
                    Rectangle(
                        windowAttributes.x,
                        windowAttributes.y,
                        windowAttributes.width,
                        windowAttributes.height) );

                // TODO: do not move the pointer when it's already inside the
                // window.
                XWarpPointer( _display, None, _handle, 0, 0, 0, 0, 0, 0 );
            }
        }
    }

    using EventHandlers =
        std::unordered_map<int, void(WindowImplementation::*)(const void*)>;
    EventHandlers _eventHandlers;

    DisplayConnection _display;
    ::Window _handle = {};

    int _xinputOpcode = 0;

    Cursor _transparentCursor = {};

    struct {
        Atom atom                 = None;
        Atom motifWmHints         = None;
        Atom netWmName            = None;
        Atom netWmState           = None;
        Atom netWmStateFullscreen = None;
        Atom utf8String           = None;
        Atom wmDeleteWindow       = None;
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
