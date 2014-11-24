#include <storm/platform/win/rendering_system_wgl.h>

#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/win/rendering_window_win.h>
#include <storm/throw_exception.h>

// ----------------------------------------------------------------------------
//  WGL_ARB_create_context extension
// ----------------------------------------------------------------------------

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB         0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB  0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);

// ----------------------------------------------------------------------------

namespace storm {

DeviceContextHandle::DeviceContextHandle( HWND windowHandle ) :
    _windowHandle( windowHandle ),
    _handle( ::GetDC(windowHandle) )
{
    if( !_handle )
        throwRuntimeError( "::GetDC has failed" );
}

DeviceContextHandle::~DeviceContextHandle() {
    ::ReleaseDC( _windowHandle, _handle );
}

RenderingContextHandle::RenderingContextHandle( HGLRC handle ) :
    _handle( handle )
{
}

RenderingContextHandle::~RenderingContextHandle() {
    ::wglDeleteContext( _handle );
}

void RenderingContextHandle::install( HDC deviceContextHandle ) const {
    if( !::wglMakeCurrent(deviceContextHandle, _handle) )
        throwRuntimeError( "::wglMakeCurrent has failed" );
}

RenderingSystemWgl::RenderingSystemWgl( HWND windowHandle ) :
    _deviceContextHandle( windowHandle )
{
    selectPixelFormat();

    RenderingContextHandle compatibilityContext(
        ::wglCreateContext(_deviceContextHandle) );
    if( !compatibilityContext )
        throwRuntimeError( "::wglCreateContext has failed" );

    compatibilityContext.install( _deviceContextHandle );

    const PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
            ::wglGetProcAddress("wglCreateContextAttribsARB") );

    if( !wglCreateContextAttribsARB )
        throw SystemRequirementsNotMet() <<
            "The 'WGL_ARB_create_context' extension is not supported";

    const int openGl_3_3_ContextAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
        0
    };

    _renderingContextHandle.reset( new RenderingContextHandle(
        wglCreateContextAttribsARB(
            _deviceContextHandle, 0, openGl_3_3_ContextAttributes)) );
    if( !_renderingContextHandle )
        throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";

    _renderingContextHandle->install( _deviceContextHandle );

    initialize();
}

void RenderingSystemWgl::endFrameRendering() {
    RenderingSystemOgl::endFrameRendering();

    if( !::SwapBuffers(_deviceContextHandle) )
        throwRuntimeError( "::SwapBuffers has failed" );
}

void RenderingSystemWgl::selectPixelFormat() {
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
    pixelFormatDescriptor.nSize = sizeof( pixelFormatDescriptor );
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER | PFD_DEPTH_DONTCARE;
    pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDescriptor.cColorBits = 24;
    pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

    const int pixelFormat =
        ::ChoosePixelFormat( _deviceContextHandle, &pixelFormatDescriptor );
    if( !pixelFormat )
        throwRuntimeError( "::ChoosePixelFormat has failed" );

    if( !::SetPixelFormat(
            _deviceContextHandle, pixelFormat, &pixelFormatDescriptor) )
        throwRuntimeError( "::SetPixelFormat has failed" );
}

RenderingSystemWgl* RenderingSystemWgl::getInstance() {
    static const std::unique_ptr<RenderingSystemWgl> instance(
        new RenderingSystemWgl(RenderingWindowWin::getInstance()->getHandle()) );
    return instance.get();
}

RenderingSystem* RenderingSystem::getInstance() {
    return RenderingSystemWgl::getInstance();
}

}