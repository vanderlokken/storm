#include <storm/platform/win/rendering_window_win.h>

#include <algorithm>
#include <memory>

#include <storm/platform/win/event_loop_win.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

void addWindowStyle( HWND handle, DWORD style ) {
    ::SetWindowLongPtr( handle, GWL_STYLE,
        ::GetWindowLongPtr(handle, GWL_STYLE) | style );
}

void removeWindowStyle( HWND handle, DWORD style ) {
    ::SetWindowLongPtr( handle, GWL_STYLE,
        ::GetWindowLongPtr(handle, GWL_STYLE) & ~style );
}

void restoreDisplayMode() {
    ::ChangeDisplaySettings( /*mode = */ nullptr, 0 );
}

}

RenderingWindowWin::RenderingWindowWin() :
    _handle( 0 ),
    _fullscreen( false ),
    _fullscreenMode( FullscreenMode() )
{
    const HINSTANCE instance = ::GetModuleHandle( 0 );

    WNDCLASS windowClass;
    windowClass.style = 0;
    windowClass.lpfnWndProc = &RenderingWindowWin::windowProcedure;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = instance;
    windowClass.hIcon = 0;
    windowClass.hCursor = ::LoadCursor( 0, IDC_ARROW );
    windowClass.hbrBackground = reinterpret_cast< HBRUSH >( COLOR_3DFACE + 1 );
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = L"Storm Rendering Window";

    const ATOM classId = ::RegisterClass( &windowClass );

    if( !classId )
        throwRuntimeError( "::RegisterClass has failed" );

    const wchar_t *className = windowClass.lpszClassName;
    const wchar_t *windowName = L"";
    const DWORD style = WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
        WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE;
    const int x = 0;
    const int y = 0;
    const int width = 0;
    const int height = 0;
    const HWND parentWindowHandle = 0;
    const HMENU menuHandle = 0;
    void *parameter = nullptr;

    _handle = ::CreateWindow(
        className,
        windowName,
        style,
        x,
        y,
        width,
        height,
        parentWindowHandle,
        menuHandle,
        instance,
        parameter );

    if( !_handle )
        throwRuntimeError( "::CreateWindow has failed" );

    ::SetWindowLongPtr(
        _handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this) );
}

RenderingWindowWin::~RenderingWindowWin() {
    ::DestroyWindow( _handle );
}

void RenderingWindowWin::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void RenderingWindowWin::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

Dimensions RenderingWindowWin::getDimensions() const {
    return _dimensions;
}

bool RenderingWindowWin::isActive() const {
    return ::GetForegroundWindow() == _handle;
}

bool RenderingWindowWin::isFullscreen() const {
    return _fullscreen;
}

void RenderingWindowWin::setWindowed( Dimensions windowDimensions ) {
    restoreDisplayMode();

    addWindowStyle( _handle, WS_CAPTION );

    const unsigned int width = windowDimensions.width;
    const unsigned int height = windowDimensions.height;

    RECT desktopRectangle = { 0, 0, 0, 0 };

    ::GetWindowRect( ::GetDesktopWindow(), &desktopRectangle );

    const unsigned int x = ( desktopRectangle.right - width ) / 2;
    const unsigned int y = ( desktopRectangle.bottom - height ) / 2;

    RECT windowRectangle = { x, y, x + width, y + height };

    const DWORD windowStyle = ::GetWindowLongPtr( _handle, GWL_STYLE );
    const BOOL  hasMenu     = ::GetMenu( _handle ) != 0;

    ::AdjustWindowRect( &windowRectangle, windowStyle, hasMenu );

    const int resultX = std::max<long>( windowRectangle.left, 0 );
    const int resultY = std::max<long>( windowRectangle.top, 0 );
    const int resultWidth = windowRectangle.right - windowRectangle.left;
    const int resultHeight = windowRectangle.bottom - windowRectangle.top;

    ::SetWindowPos( _handle, HWND_TOP,
        resultX, resultY, resultWidth, resultHeight, SWP_FRAMECHANGED );

    _fullscreen = false;
    _dimensions = windowDimensions;
}

void RenderingWindowWin::setFullscreen( FullscreenMode fullscreenMode ) {
    if( fullscreenMode.custom ) {
        DEVMODE displayMode = {};
        displayMode.dmSize = sizeof( displayMode );
        displayMode.dmPelsWidth = fullscreenMode.mode.width;
        displayMode.dmPelsHeight = fullscreenMode.mode.height;
        displayMode.dmDisplayFrequency = fullscreenMode.mode.refreshRate;
        displayMode.dmFields =
            DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        if( ::ChangeDisplaySettings(&displayMode, CDS_FULLSCREEN) !=
            DISP_CHANGE_SUCCESSFUL )
        {
            fullscreenMode = {};
            restoreDisplayMode();
        }
    } else
        restoreDisplayMode();

    removeWindowStyle( _handle, WS_CAPTION );

    const unsigned int width = ::GetSystemMetrics( SM_CXSCREEN );
    const unsigned int height = ::GetSystemMetrics( SM_CYSCREEN );

    ::SetWindowPos( _handle, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED );

    _fullscreen = true;
    _fullscreenMode = fullscreenMode;
    _dimensions = { width, height };
}

HWND RenderingWindowWin::getHandle() const {
    return _handle;
}

LRESULT CALLBACK RenderingWindowWin::windowProcedure(
    HWND windowHandle, UINT message, WPARAM firstParameter, LPARAM secondParameter )
{
    // It's not possible to safely call the 'getInstance' method here since some
    // messages are sent during the construction of an instance.
    RenderingWindowWin *instance = reinterpret_cast<RenderingWindowWin*>(
        ::GetWindowLongPtr(windowHandle, GWLP_USERDATA) );

    if( instance ) {
        ObserverList<Observer> &observers = instance->_observers;

        switch( message ) {
        case WM_ACTIVATE: {
                const bool active = LOWORD( firstParameter ) != WA_INACTIVE;

                if( instance->_fullscreen &&
                    instance->_fullscreenMode.custom )
                {
                    if( active ) {
                        instance->setFullscreen( instance->_fullscreenMode );
                    } else {
                        ::CloseWindow( instance->_handle );
                        restoreDisplayMode();
                    }
                }

                if( active )
                    observers.notify( &Observer::onFocusIn );
                else
                    observers.notify( &Observer::onFocusOut );
            }
            break;

        case WM_SIZE:
            if( firstParameter == SIZE_MINIMIZED )
                observers.notify( &Observer::onFolding );
            else if( firstParameter == SIZE_RESTORED )
                observers.notify( &Observer::onUnfolding );
            break;

        case WM_DISPLAYCHANGE:
            // TODO: fix fullscreen rendering window behaviour on display mode changes.
            break;

        case WM_COMMAND:
            if( HIWORD(firstParameter) == 1 &&
                LOWORD(firstParameter) ==
                    EventLoopWin::ToggleFullscreenModeCommand )
            {
                if( instance->_fullscreen ) {
                    observers.notify( &Observer::onWindowedModeRequest );
                } else {
                    observers.notify( &Observer::onFullscreenModeRequest );
                }
                return 0;
            }
            break;

        case WM_CLOSE:
            observers.notify( &Observer::onShutdown );

            EventLoop::getInstance()->stop();
            return 0;
        }
    }

    return ::DefWindowProc( windowHandle, message, firstParameter, secondParameter );
}

RenderingWindowWin* RenderingWindowWin::getInstance() {
    static const std::unique_ptr<RenderingWindowWin> instance( new RenderingWindowWin );
    return instance.get();
}

RenderingWindow* RenderingWindow::getInstance() {
    return RenderingWindowWin::getInstance();
}

}