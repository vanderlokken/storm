#include <storm/platform/x11/rendering_system_glx.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/platform/x11/rendering_window_x11.h>
#include <storm/throw_exception.h>

namespace storm {

RenderingSystemGlx::RenderingSystemGlx( XDisplay *display, Window window ) :
    _display( display ), _window( window )
{
    auto address = ::glXGetProcAddressARB(
        reinterpret_cast<const unsigned char*>( "glXCreateContextAttribsARB") );
    const PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
        reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>( address );

    if( !glXCreateContextAttribsARB )
        throw SystemRequirementsNotMet() <<
            "The 'GLX_ARB_create_context' extension is not supported.";

    const int frameBufferAttributes[] = {
        GLX_DOUBLEBUFFER, 1,
        0
    };

    int configNumber = 0;
    const GLXFBConfig *frameBufferConfigs = ::glXChooseFBConfig(
        _display, /*screen = */ 0, frameBufferAttributes, &configNumber);

    if( !configNumber )
        throwRuntimeError( "::glXChooseFBConfig has failed" );

    const GLXContext shareListContext = 0;
    const bool useDirectRendering = true;

    const int contextAttributes[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
#endif
        0
    };

    _context = glXCreateContextAttribsARB( _display, *frameBufferConfigs,
        shareListContext, useDirectRendering, contextAttributes );

    if( !_context )
        throwRuntimeError( "::glXCreateContextAttribsARB has failed" );

    ::glXMakeCurrent( _display, _window, _context );

    initialize();
}

RenderingSystemGlx::~RenderingSystemGlx() {
    ::glXMakeCurrent( _display, None, 0 );
    ::glXDestroyContext( _display, _context );
}

void RenderingSystemGlx::beginFrameRendering() {}

void RenderingSystemGlx::endFrameRendering() {
    ::glXSwapBuffers( _display, _window );
}

bool RenderingSystemGlx::isVsyncEnabled() const {
    unsigned int interval = 0;
    ::glXQueryDrawable(
        ::glXGetCurrentDisplay(),
        ::glXGetCurrentDrawable(),
        GLX_SWAP_INTERVAL_EXT, &interval );
    return interval != 0;
}

void RenderingSystemGlx::setVsyncEnabled( bool ) {
    // TODO: implement
}

RenderingSystemGlx* RenderingSystemGlx::getInstance() {
    const auto create = [] {
        Window window = RenderingWindowX11::getInstance()->getHandle();
        return new RenderingSystemGlx( getDisplayHandleX11(), window );
    };
    static const std::unique_ptr<RenderingSystemGlx> instance( create() );
    return instance.get();
}

RenderingSystem* RenderingSystem::getInstance() {
    return RenderingSystemGlx::getInstance();
}

}
