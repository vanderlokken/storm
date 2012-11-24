#include "RenderingSystemGlx.h"

#include "DisplayConnectionX11.h"
#include "Exception.h"
#include "RenderingWindowX11.h"

namespace storm {

RenderingSystemGlx::RenderingSystemGlx()
    : _display( DisplayConnectionX11::getInstance()->getHandle() ),
      _window( RenderingWindowX11::getInstance()->getHandle() )
{
    int visualAttributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    
    XVisualInfo *visualInformation = ::glXChooseVisual(
        _display, DefaultScreen(_display), visualAttributes );
    
    if( !visualInformation ) {
        throwRuntimeError( "::glXChooseVisual has failed" );
    }
    
    const GLXContext shareListContext = 0;
    const bool useDirectRendering = true;
    
    _context = ::glXCreateContext(
        _display, visualInformation, shareListContext, useDirectRendering );
    
    ::glXMakeCurrent( _display, _window, _context );
    
    initialize();
    return;
}

RenderingSystemGlx::~RenderingSystemGlx() noexcept {
    ::glXMakeCurrent( _display, None, 0 );
    ::glXDestroyContext( _display, _context );
    return;
}

void RenderingSystemGlx::beginFrameRendering() {
    return;
}

void RenderingSystemGlx::endFrameRendering() {
    ::glXSwapBuffers( _display, _window );
    return;
}

void RenderingSystemGlx::setColorBufferFormat( ColorBufferFormat ) {
    throwRuntimeError( "Not implemented" );
}

void RenderingSystemGlx::setDepthBufferFormat( DepthBufferFormat ) {
    return;
}

std::shared_ptr<RenderingSystemGlx> RenderingSystemGlx::getInstance() {
    static const std::shared_ptr<RenderingSystemGlx> instance( new RenderingSystemGlx );
    return instance;
}

std::shared_ptr<RenderingSystem> RenderingSystem::getInstance() {
    return RenderingSystemGlx::getInstance();
}

}
