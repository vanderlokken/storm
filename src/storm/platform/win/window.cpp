#include <storm/window.h>

#include <array>

#include <storm/platform/win/api_win.h>

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
    static constexpr wchar_t *windowClassName = L"window";

public:
    WindowImplementation() {
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

        // TODO: apply lock if needed
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

        switch( message ) {
        case WM_ACTIVATE:
            if( LOWORD(wParam) == WA_INACTIVE ) {
                runCallback( self->_observer.onFocusLost );
            } else {
                runCallback( self->_observer.onFocusReceived );
            }
            break;

        case WM_CLOSE:
            runCallback( self->_observer.onShutdownRequested );
            return 0;

        case WM_DISPLAYCHANGE:
            SetWindowPos(
                window,
				nullptr,
                0,
                0,
                GetSystemMetrics(SM_CXSCREEN),
                GetSystemMetrics(SM_CYSCREEN),
                SWP_NOACTIVATE | SWP_NOZORDER );
            break;

        case WM_INPUT:
            self->onInputEventReceived( reinterpret_cast<HRAWINPUT>(lParam) );
            break;

        case WM_SETCURSOR:
            if( !self->_isPointerVisible && LOWORD(lParam) == HTCLIENT ) {
                SetCursor( nullptr );
            }
            break;

        case WM_SIZE:
            if( wParam == SIZE_RESTORED ) {
                self->onResized();
            }
            break;
        }

        return DefWindowProc( window, message, wParam, lParam );
    }

    void onInputEventReceived( HRAWINPUT handle ) const {
        RAWINPUT data = {};
        UINT dataSize = sizeof( data );

        GetRawInputData(
            handle, RID_INPUT, &data, &dataSize, sizeof(data.header) );

        if( data.header.dwType == RIM_TYPEMOUSE ) {
            using Btn = Mouse::Button;

            for( const auto [mask, button] : {
                    std::make_pair(RI_MOUSE_BUTTON_1_DOWN, Btn::Left),
                    std::make_pair(RI_MOUSE_BUTTON_2_DOWN, Btn::Right),
                    std::make_pair(RI_MOUSE_BUTTON_3_DOWN, Btn::Middle),
                    std::make_pair(RI_MOUSE_BUTTON_4_DOWN, Btn::SideFirst),
                    std::make_pair(RI_MOUSE_BUTTON_5_DOWN, Btn::SideSecond)} ) {
                if( data.data.mouse.ulButtons & mask ) {
                    runCallback( _observer.onMouseButtonPressed, button );
                }
            }

            for( const auto [mask, button] : {
                    std::make_pair(RI_MOUSE_BUTTON_1_UP, Btn::Left),
                    std::make_pair(RI_MOUSE_BUTTON_2_UP, Btn::Right),
                    std::make_pair(RI_MOUSE_BUTTON_3_UP, Btn::Middle),
                    std::make_pair(RI_MOUSE_BUTTON_4_UP, Btn::SideFirst),
                    std::make_pair(RI_MOUSE_BUTTON_5_UP, Btn::SideSecond)} ) {
                if( data.data.mouse.ulButtons & mask ) {
                    runCallback( _observer.onMouseButtonReleased, button );
                }
            }
        }

        if( data.header.dwType == RIM_TYPEKEYBOARD ) {
            //
        }
    }

    void onResized() {
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

    HWND _handle = nullptr;

    WindowObserver _observer;

    std::string _title;
    Dimensions _dimensions;

    bool _isPointerVisible = true;
    bool _isPointerLocked = false;
};

} // namespace

std::unique_ptr<Window> Window::create() {
    return std::make_unique<WindowImplementation>();
}

}
