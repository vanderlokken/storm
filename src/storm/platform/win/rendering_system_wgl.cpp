#include <storm/platform/win/rendering_system_wgl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/win/rendering_window_win.h>

// ----------------------------------------------------------------------------
//  WGL_ARB_create_context extension
// ----------------------------------------------------------------------------

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

// ----------------------------------------------------------------------------

namespace storm {

RenderingSystemWgl::RenderingSystemWgl()
    : _renderingWindowHandle( RenderingWindowWin::getInstance()->getHandle() ),
      _deviceContextHandle( ::GetDC(_renderingWindowHandle) ),
      _renderingContextHandle( 0 )
{
    if( !_deviceContextHandle )
        throwRuntimeError( "::GetDC has failed" );

    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
    pixelFormatDescriptor.nSize = sizeof( pixelFormatDescriptor );
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits = 24;
    pixelFormatDescriptor.cAlphaBits = 0;
    pixelFormatDescriptor.cAccumBits = 0;
    pixelFormatDescriptor.cDepthBits = 24;
    pixelFormatDescriptor.cStencilBits = 0;
    pixelFormatDescriptor.cAuxBuffers = 0;
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

    const int pixelFormat =
        ::ChoosePixelFormat( _deviceContextHandle, &pixelFormatDescriptor );
    if( !pixelFormat )
        throwRuntimeError( "::ChoosePixelFormat has failed" );

    if( !::SetPixelFormat(
            _deviceContextHandle, pixelFormat, &pixelFormatDescriptor) )
        throwRuntimeError( "::SetPixelFormat has failed" );

    HGLRC compatibilityContext = ::wglCreateContext( _deviceContextHandle );
    if( !compatibilityContext )
        throwRuntimeError( "::wglCreateContext has failed" );

    ::wglMakeCurrent( _deviceContextHandle, compatibilityContext );

    const PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
            ::wglGetProcAddress("wglCreateContextAttribsARB") );

    const int openGl_3_3_ContextAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };

    _renderingContextHandle = wglCreateContextAttribsARB(
        _deviceContextHandle, 0, openGl_3_3_ContextAttributes );

    ::wglDeleteContext( compatibilityContext );

    if( !_renderingContextHandle )
        throwRuntimeError( "::wglCreateContextAttribsARB has failed" );

    if( !::wglMakeCurrent(_deviceContextHandle, _renderingContextHandle) )
        throwRuntimeError( "::wglMakeCurrent has failed" );

    initialize();
    return;
}

RenderingSystemWgl::~RenderingSystemWgl() {
    ::wglDeleteContext( _renderingContextHandle );
    ::ReleaseDC( _renderingWindowHandle, _deviceContextHandle );
    return;
}

void RenderingSystemWgl::beginFrameRendering() {
    return;
}

void RenderingSystemWgl::endFrameRendering() {
    if( !::SwapBuffers(_deviceContextHandle) )
        throwRuntimeError( "::SwapBuffers has failed" );
    return;
}

void RenderingSystemWgl::setColorBufferFormat( ColorBufferFormat ) {
    throwNotImplemented();
}

void RenderingSystemWgl::setDepthBufferFormat( DepthBufferFormat ) {
    return;
    // throwNotImplemented();
}

RenderingSystemWgl* RenderingSystemWgl::getInstance() {
    static const std::unique_ptr<RenderingSystemWgl> instance( new RenderingSystemWgl );
    return instance.get();
}

RenderingSystem* RenderingSystem::getInstance() {
    return RenderingSystemWgl::getInstance();
}

}