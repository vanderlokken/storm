#include "RenderingWindowWin.h"

#include "Exception.h"

namespace storm {

RenderingWindowWin::RenderingWindowWin()
    : _handle( 0 ),
      _fullscreen( false )
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
    const DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_POPUP | WS_SYSMENU | WS_VISIBLE;
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

    return;
}

RenderingWindowWin::~RenderingWindowWin() noexcept {
    ::DestroyWindow( _handle );
    return;
}

Dimensions RenderingWindowWin::getDimensions() const noexcept {
    return _dimensions;
}

bool RenderingWindowWin::isActive() const noexcept {
    return ::GetForegroundWindow() == _handle;
}

bool RenderingWindowWin::isFullscreen() const noexcept {
    return _fullscreen;
}

void RenderingWindowWin::setWindowed( Dimensions windowDimensions ) {
    const unsigned int width = windowDimensions.getWidth();
    const unsigned int height = windowDimensions.getHeight();
    
    RECT desktopRectangle = { 0, 0, 0, 0 };
    
    ::GetWindowRect( ::GetDesktopWindow(), &desktopRectangle );
    
    const unsigned int x = ( desktopRectangle.right - width ) / 2;
    const unsigned int y = ( desktopRectangle.bottom - height ) / 2;
    
    RECT windowRectangle = { x, y, x + width, y + height };
    
    const DWORD windowStyle = ::GetWindowLongPtr( _handle, GWL_STYLE );
    const BOOL  hasMenu     = ::GetMenu( _handle ) != 0;
    
    ::AdjustWindowRect( &windowRectangle, windowStyle, hasMenu );
    
    const int resultX = windowRectangle.left;
    const int resultY = windowRectangle.top;
    const int resultWidth = windowRectangle.right - windowRectangle.left;
    const int resultHeight = windowRectangle.bottom - windowRectangle.top;
    const BOOL repaint = FALSE;
    
    ::MoveWindow( _handle, resultX, resultY, resultWidth, resultHeight, repaint );
    
    _fullscreen = false;
    _dimensions = windowDimensions;
    return;
}

void RenderingWindowWin::setFullscreen() {
    throwRuntimeError( "Not implemented" );
}

HWND RenderingWindowWin::getHandle() const noexcept {
    return _handle;
}

LRESULT CALLBACK RenderingWindowWin::windowProcedure(
    HWND windowHandle, UINT message, WPARAM firstParameter, LPARAM secondParameter ) noexcept
{
    if( message == WM_DESTROY )
        ::PostQuitMessage( 0 );

    return ::DefWindowProc( windowHandle, message, firstParameter, secondParameter );
}

std::shared_ptr<RenderingWindowWin> RenderingWindowWin::getInstance() {
    static std::shared_ptr<RenderingWindowWin> instance( new RenderingWindowWin );
    return instance;
}

std::shared_ptr<RenderingWindow> RenderingWindow::getInstance() {
    return RenderingWindowWin::getInstance();
}

}