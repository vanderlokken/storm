#include "RenderingSystemWgl.h"

#include "Exception.h"
#include "RenderingWindowWin.h"

namespace storm {

RenderingSystemWgl::RenderingSystemWgl()
    : _renderingWindowHandle( 0 ),
      _deviceContextHandle( 0 ),
      _renderingContextHandle( 0 )
{
    _renderingWindowHandle = RenderingWindowWin::getInstance()->getHandle();
    
    _deviceContextHandle = ::GetDC( _renderingWindowHandle );
    
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

    int pixelFormat = ::ChoosePixelFormat( _deviceContextHandle, &pixelFormatDescriptor );
        
    if( !pixelFormat )
        throwRuntimeError( "::ChoosePixelFormat has failed" );
        
    const BOOL formatSet = ::SetPixelFormat( _deviceContextHandle, pixelFormat, &pixelFormatDescriptor );
    
    if( !formatSet )
        throwRuntimeError( "::SetPixelFormat has failed" );

    _renderingContextHandle = ::wglCreateContext( _deviceContextHandle );
    
    if( !_renderingContextHandle )
        throwRuntimeError( "::wglCreateContext has failed" );
    
    const BOOL succeeded = ::wglMakeCurrent( _deviceContextHandle, _renderingContextHandle );
    
    if( !succeeded )
        throwRuntimeError( "::wglMakeCurrent has failed" );
        
    initialize();
    return;
}

RenderingSystemWgl::~RenderingSystemWgl() noexcept {
    ::wglMakeCurrent( 0, 0 ); 
    ::ReleaseDC( _renderingWindowHandle, _deviceContextHandle );
    ::wglDeleteContext( _renderingContextHandle );
    return;
}

void RenderingSystemWgl::beginFrameRendering() {
    return;
}

void RenderingSystemWgl::endFrameRendering() {
    const BOOL succeeded = ::SwapBuffers( _deviceContextHandle );
    
    if( !succeeded )
        throwRuntimeError( "::SwapBuffers has failed" );
    return;
}

void RenderingSystemWgl::setColorBufferFormat( ColorBufferFormat ) {
    throwRuntimeError( "Not implemented" );
}

void RenderingSystemWgl::setDepthBufferFormat( DepthBufferFormat ) {
    return;
}

std::shared_ptr<RenderingSystemWgl> RenderingSystemWgl::getInstance() {
    static const std::shared_ptr<RenderingSystemWgl> instance( new RenderingSystemWgl );
    return instance; 
}

std::shared_ptr<RenderingSystem> RenderingSystem::getInstance() {
    return RenderingSystemWgl::getInstance(); 
}

}