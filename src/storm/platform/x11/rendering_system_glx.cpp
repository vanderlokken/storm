#include <storm/platform/x11/rendering_system_glx.h>

#include <storm/exception.h>
#include <storm/platform/x11/display_connection_x11.h>
#include <storm/platform/x11/rendering_window_x11.h>

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

RenderingSystemGlx::~RenderingSystemGlx() {
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

RenderingSystemGlx* RenderingSystemGlx::getInstance() {
    static const std::unique_ptr<RenderingSystemGlx> instance( new RenderingSystemGlx );
    return instance.get();
}

RenderingSystem* RenderingSystem::getInstance() {
    return RenderingSystemGlx::getInstance();
}

}
