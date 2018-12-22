#include <storm/window.h>

#include <array>
#include <optional>
#include <unordered_map>

#include <storm/platform/win/api_win.h>

#include <kbd.h>

namespace storm {

namespace {

using Key = Keyboard::Key;

struct ScanCodeMapping {
    std::optional<Key> normal;
    std::optional<Key> escaped;
};

constexpr std::array<ScanCodeMapping, 95> scanCodeMappings = {
    /*0x00*/ ScanCodeMapping {std::nullopt,        std::nullopt},
    /*0x01*/ ScanCodeMapping {Key::Escape,         std::nullopt},
    /*0x02*/ ScanCodeMapping {Key::Digit1,         std::nullopt},
    /*0x03*/ ScanCodeMapping {Key::Digit2,         std::nullopt},
    /*0x04*/ ScanCodeMapping {Key::Digit3,         std::nullopt},
    /*0x05*/ ScanCodeMapping {Key::Digit4,         std::nullopt},
    /*0x06*/ ScanCodeMapping {Key::Digit5,         std::nullopt},
    /*0x07*/ ScanCodeMapping {Key::Digit6,         std::nullopt},
    /*0x08*/ ScanCodeMapping {Key::Digit7,         std::nullopt},
    /*0x09*/ ScanCodeMapping {Key::Digit8,         std::nullopt},
    /*0x0a*/ ScanCodeMapping {Key::Digit9,         std::nullopt},
    /*0x0b*/ ScanCodeMapping {Key::Digit0,         std::nullopt},
    /*0x0c*/ ScanCodeMapping {Key::Minus,          std::nullopt},
    /*0x0d*/ ScanCodeMapping {Key::Plus,           std::nullopt},
    /*0x0e*/ ScanCodeMapping {Key::Backspace,      std::nullopt},
    /*0x0f*/ ScanCodeMapping {Key::Tab,            std::nullopt},
    /*0x10*/ ScanCodeMapping {Key::Q,              std::nullopt},
    /*0x11*/ ScanCodeMapping {Key::W,              std::nullopt},
    /*0x12*/ ScanCodeMapping {Key::E,              std::nullopt},
    /*0x13*/ ScanCodeMapping {Key::R,              std::nullopt},
    /*0x14*/ ScanCodeMapping {Key::T,              std::nullopt},
    /*0x15*/ ScanCodeMapping {Key::Y,              std::nullopt},
    /*0x16*/ ScanCodeMapping {Key::U,              std::nullopt},
    /*0x17*/ ScanCodeMapping {Key::I,              std::nullopt},
    /*0x18*/ ScanCodeMapping {Key::O,              std::nullopt},
    /*0x19*/ ScanCodeMapping {Key::P,              std::nullopt},
    /*0x1a*/ ScanCodeMapping {Key::LeftBracket,    std::nullopt},
    /*0x1b*/ ScanCodeMapping {Key::RightBracket,   std::nullopt},
    /*0x1c*/ ScanCodeMapping {Key::Enter,          Key::KeypadEnter},
    /*0x1d*/ ScanCodeMapping {Key::LeftControl,    Key::RightControl},
    /*0x1e*/ ScanCodeMapping {Key::A,              std::nullopt},
    /*0x1f*/ ScanCodeMapping {Key::S,              std::nullopt},
    /*0x20*/ ScanCodeMapping {Key::D,              std::nullopt},
    /*0x21*/ ScanCodeMapping {Key::F,              std::nullopt},
    /*0x22*/ ScanCodeMapping {Key::G,              std::nullopt},
    /*0x23*/ ScanCodeMapping {Key::H,              std::nullopt},
    /*0x24*/ ScanCodeMapping {Key::J,              std::nullopt},
    /*0x25*/ ScanCodeMapping {Key::K,              std::nullopt},
    /*0x26*/ ScanCodeMapping {Key::L,              std::nullopt},
    /*0x27*/ ScanCodeMapping {Key::Semicolon,      std::nullopt},
    /*0x28*/ ScanCodeMapping {Key::Apostrophe,     std::nullopt},
    /*0x29*/ ScanCodeMapping {Key::Tilde,          std::nullopt},
    /*0x2a*/ ScanCodeMapping {Key::LeftShift,      std::nullopt},
    /*0x2b*/ ScanCodeMapping {Key::Backslash,      std::nullopt},
    /*0x2c*/ ScanCodeMapping {Key::Z,              std::nullopt},
    /*0x2d*/ ScanCodeMapping {Key::X,              std::nullopt},
    /*0x2e*/ ScanCodeMapping {Key::C,              std::nullopt},
    /*0x2f*/ ScanCodeMapping {Key::V,              std::nullopt},
    /*0x30*/ ScanCodeMapping {Key::B,              std::nullopt},
    /*0x31*/ ScanCodeMapping {Key::N,              std::nullopt},
    /*0x32*/ ScanCodeMapping {Key::M,              std::nullopt},
    /*0x33*/ ScanCodeMapping {Key::Comma,          std::nullopt},
    /*0x34*/ ScanCodeMapping {Key::Period,         std::nullopt},
    /*0x35*/ ScanCodeMapping {Key::Slash,          Key::KeypadSlash},
    /*0x36*/ ScanCodeMapping {Key::RightShift,     std::nullopt},
    /*0x37*/ ScanCodeMapping {Key::KeypadAsterisk, Key::PrintScreen},
    /*0x38*/ ScanCodeMapping {Key::LeftAlter,      Key::RightAlter},
    /*0x39*/ ScanCodeMapping {Key::Space,          std::nullopt},
    /*0x3a*/ ScanCodeMapping {Key::CapsLock,       std::nullopt},
    /*0x3b*/ ScanCodeMapping {Key::F1,             std::nullopt},
    /*0x3c*/ ScanCodeMapping {Key::F2,             std::nullopt},
    /*0x3d*/ ScanCodeMapping {Key::F3,             std::nullopt},
    /*0x3e*/ ScanCodeMapping {Key::F4,             std::nullopt},
    /*0x3f*/ ScanCodeMapping {Key::F5,             std::nullopt},
    /*0x40*/ ScanCodeMapping {Key::F6,             std::nullopt},
    /*0x41*/ ScanCodeMapping {Key::F7,             std::nullopt},
    /*0x42*/ ScanCodeMapping {Key::F8,             std::nullopt},
    /*0x43*/ ScanCodeMapping {Key::F9,             std::nullopt},
    /*0x44*/ ScanCodeMapping {Key::F10,            std::nullopt},
    /*0x45*/ ScanCodeMapping {Key::NumLock,        std::nullopt},
    /*0x46*/ ScanCodeMapping {Key::ScrollLock,     Key::Pause},
    /*0x47*/ ScanCodeMapping {Key::Keypad7,        Key::Home},
    /*0x48*/ ScanCodeMapping {Key::Keypad8,        Key::Up},
    /*0x49*/ ScanCodeMapping {Key::Keypad9,        Key::PageUp},
    /*0x4a*/ ScanCodeMapping {Key::KeypadMinus,    std::nullopt},
    /*0x4b*/ ScanCodeMapping {Key::Keypad4,        Key::Left},
    /*0x4c*/ ScanCodeMapping {Key::Keypad5,        std::nullopt},
    /*0x4d*/ ScanCodeMapping {Key::Keypad6,        Key::Right},
    /*0x4e*/ ScanCodeMapping {Key::KeypadPlus,     std::nullopt},
    /*0x4f*/ ScanCodeMapping {Key::Keypad1,        Key::End},
    /*0x50*/ ScanCodeMapping {Key::Keypad2,        Key::Down},
    /*0x51*/ ScanCodeMapping {Key::Keypad3,        Key::PageDown},
    /*0x52*/ ScanCodeMapping {Key::Keypad0,        Key::Insert},
    /*0x53*/ ScanCodeMapping {Key::KeypadDelete,   Key::Delete},
    /*0x54*/ ScanCodeMapping {Key::PrintScreen,    std::nullopt},
    /*0x55*/ ScanCodeMapping {std::nullopt,        std::nullopt},
    /*0x56*/ ScanCodeMapping {std::nullopt,        std::nullopt},
    /*0x57*/ ScanCodeMapping {Key::F11,            std::nullopt},
    /*0x58*/ ScanCodeMapping {Key::F12,            std::nullopt},
    /*0x59*/ ScanCodeMapping {std::nullopt,        std::nullopt},
    /*0x5a*/ ScanCodeMapping {std::nullopt,        std::nullopt},
    /*0x5b*/ ScanCodeMapping {std::nullopt,        Key::LeftCommand},
    /*0x5c*/ ScanCodeMapping {std::nullopt,        Key::RightCommand},
    /*0x5d*/ ScanCodeMapping {std::nullopt,        Key::Menu},
};

template <class T, class... Args>
void runCallback( const std::function<T> &callback, Args&&... args ) {
    if( callback ) {
        callback( std::forward<Args>(args)... );
    }
}

class WindowImplementation : public Window {
private:
    static constexpr wchar_t *windowClassName = L"window";

public:
    WindowImplementation() {
        _isKeyPressed.reserve( static_cast<size_t>(Key::Count) );

        _windowMessageHandlers = {
            {WM_ACTIVATEAPP,   &WindowImplementation::onWmActivateApp},
            {WM_CLOSE,         &WindowImplementation::onWmClose},
            {WM_DISPLAYCHANGE, &WindowImplementation::onWmDisplayChange},
            {WM_INPUT,         &WindowImplementation::onWmInput},
            {WM_SETCURSOR,     &WindowImplementation::onWmSetCursor},
            {WM_SIZE,          &WindowImplementation::onWmSize},
        };

        registerWindowClass();

        _dimensions = Dimensions {
            static_cast<unsigned>( GetSystemMetrics(SM_CXSCREEN) ),
            static_cast<unsigned>( GetSystemMetrics(SM_CYSCREEN) )
        };

        _handle = CreateWindow(
            windowClassName,          // class
            L"",                      // title
            WS_POPUP,                 // style
            0,                        // x
            0,                        // y
            _dimensions.width,        // width
            _dimensions.height,       // height
            nullptr,                  // parent
            nullptr,                  // menu
            GetModuleHandle(nullptr), // instance
            this                      // data
        );

        registerInputDevices();
        setPixelFormat();
    }

    ~WindowImplementation() {
        DestroyWindow( _handle );
    }

    WindowImplementation(
        const WindowImplementation& ) = delete;
    WindowImplementation& operator = (
        const WindowImplementation& ) = delete;

    void processEvents() override {
        MSG message = {};

        while( PeekMessage(&message, _handle, 0, 0, PM_REMOVE) ) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }
    }

    void setObserver( WindowObserver observer ) override {
        _observer = std::move( observer );
    }

    void* getHandle() const override {
        return _handle;
    }

    Dimensions getDimensions() const override {
        return _dimensions;
    }

    void setWindowedFullscreenMode() override {
        SetWindowPos(
            _handle,
            nullptr,
            0,
            0,
            GetSystemMetrics(SM_CXSCREEN),
            GetSystemMetrics(SM_CYSCREEN),
            SWP_NOACTIVATE | SWP_NOZORDER );

        _isFullscreen = true;
    }

    void setWindowedMode( Dimensions dimensions ) override {
        SetWindowPos(
            _handle,
            nullptr,
            (GetSystemMetrics(SM_CXSCREEN) -
                static_cast<int>(dimensions.width)) / 2,
            (GetSystemMetrics(SM_CYSCREEN) -
                static_cast<int>(dimensions.height)) / 2,
            dimensions.width,
            dimensions.height,
            SWP_NOACTIVATE | SWP_NOZORDER );

        _isFullscreen = false;
    }

    bool isVisible() const override {
        return (GetWindowLongPtr(_handle, GWL_STYLE) & WS_VISIBLE) != 0;
    }

    void setVisible( bool visible ) override {
        ShowWindow( _handle, visible ? SW_SHOW : SW_HIDE );
    }

    bool hasFocus() const override {
        return GetActiveWindow() == _handle;
    }

    std::string_view getTitle() const override {
        return _title;
    }

    void setTitle( std::string title ) override {
        std::wstring buffer;

        if( !title.empty() ) {
            const int size = MultiByteToWideChar(
                CP_UTF8,
                0,
                title.data(), static_cast<int>(title.size()),
                buffer.data(), static_cast<int>(buffer.size()) );

            buffer.resize( static_cast<size_t>(size) );

            MultiByteToWideChar(
                CP_UTF8,
                0,
                title.data(), static_cast<int>(title.size()),
                buffer.data(), static_cast<int>(buffer.size()) );
        }

        SetWindowText( _handle, buffer.data() );

        _title = std::move( title );
    }

    bool isPointerVisible() const override {
        return _isPointerVisible;
    }

    void setPointerVisible( bool visible ) override {
        _isPointerVisible = visible;
    }

    bool isPointerLocked() const override {
        return _isPointerLocked;
    }

    void setPointerLocked( bool locked ) override {
        _isPointerLocked = locked;
    }

private:
    static void registerWindowClass() {
        WNDCLASS classDescription;
        classDescription.style = 0;
        classDescription.lpfnWndProc = windowProcedure;
        classDescription.cbClsExtra = 0;
        classDescription.cbWndExtra = 0;
        classDescription.hInstance = GetModuleHandle( nullptr );
        classDescription.hIcon = nullptr;
        classDescription.hCursor = LoadCursor( nullptr, IDC_ARROW );
        classDescription.hbrBackground =
            reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 );
        classDescription.lpszMenuName = nullptr;
        classDescription.lpszClassName = windowClassName;

        RegisterClass( &classDescription );
    }

    void registerInputDevices() const {
        // See the "Top-Level Collections Opened by Windows for System Use" page
        const USHORT hidUsagePageGeneric = 0x01;
        const USHORT hidUsageGenericMouse = 0x02;
        const USHORT hidUsageGenericKeyboard = 0x06;

        const std::array<RAWINPUTDEVICE, 2> devices = {
            RAWINPUTDEVICE {
                hidUsagePageGeneric, hidUsageGenericMouse, 0, _handle},
            RAWINPUTDEVICE {
                hidUsagePageGeneric, hidUsageGenericKeyboard, 0, _handle}
        };

        RegisterRawInputDevices(
            devices.data(),
            static_cast<UINT>(devices.size()),
            sizeof(RAWINPUTDEVICE) );
    }

    void setPixelFormat() const {
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
        pixelFormatDescriptor.nSize = sizeof( pixelFormatDescriptor );
        pixelFormatDescriptor.nVersion = 1;
        pixelFormatDescriptor.dwFlags =
            PFD_DEPTH_DONTCARE |
            PFD_DOUBLEBUFFER |
            PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL;
        pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDescriptor.cColorBits = 24;
        pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

        const HDC deviceContext = GetDC( _handle );

        const int pixelFormat =
            ChoosePixelFormat( deviceContext, &pixelFormatDescriptor );

        SetPixelFormat( deviceContext, pixelFormat, &pixelFormatDescriptor );
        ReleaseDC( _handle, deviceContext );
    }

    static LRESULT CALLBACK windowProcedure(
        HWND window, UINT message, WPARAM wParam, LPARAM lParam )
    {
        if( message == WM_NCCREATE ) {
            const CREATESTRUCT *parameters =
                reinterpret_cast<const CREATESTRUCT*>( lParam );

            SetWindowLongPtr(
                window,
                GWLP_USERDATA,
                reinterpret_cast<LONG_PTR>(parameters->lpCreateParams) );
        }

        WindowImplementation *self = reinterpret_cast<WindowImplementation*>(
            GetWindowLongPtr(window, GWLP_USERDATA) );

        const auto iterator = self->_windowMessageHandlers.find( message );

        if( iterator != self->_windowMessageHandlers.end() ) {
            const auto handler = iterator->second;

            if( const std::optional<LRESULT> result =
                    (self->*handler)(wParam, lParam) ) {
                return *result;
            }
        }

        return DefWindowProc( window, message, wParam, lParam );
    }

    std::optional<LRESULT> onWmActivateApp( WPARAM wParam, LPARAM ) {
        if( wParam == TRUE ) {
            runCallback( _observer.onFocusReceived );

            if( _isPointerLocked ) {

            }
        } else {
            ClipCursor( nullptr );
            runCallback( _observer.onFocusLost );
        }

        return std::nullopt;
    }

    std::optional<LRESULT> onWmClose( WPARAM, LPARAM ) {
        runCallback( _observer.onShutdownRequested );

        return 0;
    }

    std::optional<LRESULT> onWmDisplayChange( WPARAM, LPARAM ) {
        if( _isFullscreen ) {
            setWindowedFullscreenMode();
        }

        return std::nullopt;
    }

    std::optional<LRESULT> onWmInput( WPARAM, LPARAM lParam ) {
        RAWINPUT rawInput = {};
        UINT rawInputSize = sizeof( rawInput );

        GetRawInputData(
            reinterpret_cast<HRAWINPUT>(lParam),
            RID_INPUT,
            &rawInput,
            &rawInputSize,
            sizeof(rawInput.header) );

        if( rawInput.header.dwType == RIM_TYPEMOUSE ) {
            onRawMouseInput( rawInput.data.mouse );
        }

        if( rawInput.header.dwType == RIM_TYPEKEYBOARD ) {
            onRawKeyboardInput( rawInput.data.keyboard );
        }

        return std::nullopt;
    }

    std::optional<LRESULT> onWmSetCursor( WPARAM, LPARAM lParam ) {
        if( LOWORD(lParam) == HTCLIENT ) {
            if( _isPointerLocked ) {

            } else {
                ClipCursor( nullptr );
            }

            if( !_isPointerVisible ) {
                SetCursor( nullptr );
                return TRUE;
            }
        }

        return std::nullopt;
    }

    std::optional<LRESULT> onWmSize( WPARAM wParam, LPARAM ) {
        if( wParam == SIZE_RESTORED ) {
            RECT rectangle = {};
            GetClientRect( _handle, &rectangle );

            const Dimensions dimensions = {
                static_cast<unsigned int>(rectangle.right),
                static_cast<unsigned int>(rectangle.bottom)
            };

            if( dimensions.width != _dimensions.width ||
                dimensions.height != _dimensions.height)
            {
                _dimensions = dimensions;
                runCallback( _observer.onResized );
            }
        }

        return std::nullopt;
    }

    void onRawMouseInput( const RAWMOUSE &mouse ) const {
        using Button = Mouse::Button;

        for( const auto [mask, button] : {
                std::make_pair(RI_MOUSE_BUTTON_1_DOWN, Button::Left),
                std::make_pair(RI_MOUSE_BUTTON_2_DOWN, Button::Right),
                std::make_pair(RI_MOUSE_BUTTON_3_DOWN, Button::Middle),
                std::make_pair(RI_MOUSE_BUTTON_4_DOWN, Button::SideFirst),
                std::make_pair(RI_MOUSE_BUTTON_5_DOWN, Button::SideSecond)} ) {
            if( mouse.ulButtons & mask ) {
                runCallback( _observer.onMouseButtonPressed, button );
            }
        }

        for( const auto [mask, button] : {
                std::make_pair(RI_MOUSE_BUTTON_1_UP, Button::Left),
                std::make_pair(RI_MOUSE_BUTTON_2_UP, Button::Right),
                std::make_pair(RI_MOUSE_BUTTON_3_UP, Button::Middle),
                std::make_pair(RI_MOUSE_BUTTON_4_UP, Button::SideFirst),
                std::make_pair(RI_MOUSE_BUTTON_5_UP, Button::SideSecond)} ) {
            if( mouse.ulButtons & mask ) {
                runCallback( _observer.onMouseButtonReleased, button );
            }
        }

        if( mouse.ulButtons & RI_MOUSE_WHEEL ) {
            const float normalizationFactor = 1 / 120.0f;
            runCallback(
                _observer.onMouseWheelRotated,
                normalizationFactor * static_cast<SHORT>(mouse.usButtonData) );
        }

        if( (mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == 0 &&
                (mouse.lLastX || mouse.lLastY) ) {
            runCallback(
                _observer.onMouseMotion,
                IntVector2d(
                    mouse.lLastX,
                    mouse.lLastY
                ));
        }
    }

    void onRawKeyboardInput( const RAWKEYBOARD &keyboard ) {
        auto processKey = [=]( Key key ) {
            const bool isPressed = (keyboard.Flags & RI_KEY_BREAK) == 0;

            if( isPressed ) {
                if( !_isKeyPressed[key] ) {
                    runCallback(  _observer.onKeyboardKeyPressed, key );
                } else {
                    runCallback( _observer.onKeyboardKeyRepeated, key );
                }
            } else {
                runCallback( _observer.onKeyboardKeyReleased, key );
            }

            _isKeyPressed[key] = isPressed;
        };

        if( keyboard.Flags & RI_KEY_E1 ) {
            // For some reason the 'Pause' key is special and produces the
            // following scan code sequence: 0xe1 0x1d 0x45 0xe1 0x9d 0xc5
            const USHORT pauseKeyScanCode = 0x1d;

            if( keyboard.MakeCode == pauseKeyScanCode ) {
                processKey( Key::Pause );
            }

            return;
        }

        if( keyboard.MakeCode < scanCodeMappings.size() ) {
            const ScanCodeMapping &mapping =
                scanCodeMappings[keyboard.MakeCode];

            if( const std::optional<Key> &key = (keyboard.Flags & RI_KEY_E0) ?
                    mapping.escaped : mapping.normal ) {
                // If a keypad key is pressed when NumLock is on and any 'Shift'
                // key is down, Windows generates two events with the same
                // 'MakeCode' value but different 'VKey' values. The following
                // condition allows to ignore one of these two events.
                if( keyboard.VKey == VK_SHIFT &&
                        (*key != Key::LeftShift && *key != Key::RightShift) ) {
                    return;
                }

                // This is needed to bypass the 0x45 scan code, which is
                // produced when the 'Pause' key is pressed and which otherwise
                // would be interpreted as a 'NumLock' key press.
                if( keyboard.VKey == VK__none_ && *key == Key::NumLock ) {
                    return;
                }

                processKey( *key );
            }
        }
    }

    HWND _handle = nullptr;

    WindowObserver _observer;

    std::string _title;
    Dimensions _dimensions;

    bool _isFullscreen = true;

    bool _isPointerVisible = true;
    bool _isPointerLocked = false;

    std::unordered_map<Key, bool> _isKeyPressed;

    using WindowMessageHandlers = std::unordered_map<
        UINT, std::optional<LRESULT>(WindowImplementation::*)(WPARAM, LPARAM)>;
    WindowMessageHandlers _windowMessageHandlers;
};

} // namespace

Window::Pointer Window::create() {
    return std::make_shared<WindowImplementation>();
}

}
