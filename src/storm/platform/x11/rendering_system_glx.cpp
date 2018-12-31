#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

namespace storm {

namespace {

class RenderingSystemGlx : public RenderingSystemOgl {
public:
    RenderingSystemGlx() :
        _defaultWindow( Window::create() )
    {
        const auto glXCreateContextAttribsARB =
            reinterpret_cast<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
                glXGetProcAddress(
                    reinterpret_cast<const unsigned char*>(
                        "glXCreateContextAttribsARB")) );

        if( !glXCreateContextAttribsARB ) {
            throw SystemRequirementsNotMet() <<
                "The 'GLX_ARB_create_context' extension is not supported.";
        }

        const int contextAttributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 3,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
    #ifndef NDEBUG
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
    #endif
            0
        };

        _context = glXCreateContextAttribsARB(
            _display,
            chooseFramebufferConfig(),
            0,    // shareListContext
            true, // useDirectRendering
            contextAttributes );

        if( !_context ) {
            throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
        }

        glXMakeCurrent( _display, getWindowHandle(), _context );

        initialize();
    }

    ~RenderingSystemGlx() {
        glXMakeCurrent( _display, None, 0 );
        glXDestroyContext( _display, _context );
    }

    Window::Pointer getOutputWindow() const override {
        return _outputWindow;
    }

    void setOutputWindow( Window::Pointer window ) override {
        _outputWindow = std::move( window );

        glXMakeCurrent( _display, getWindowHandle(), _context );
    }

    void presentBackbuffer() override {
        glXSwapBuffers( _display, getWindowHandle() );
    }

    bool isVsyncEnabled() const override {
        unsigned int interval = 0;

        glXQueryDrawable(
            glXGetCurrentDisplay(),
            glXGetCurrentDrawable(),
            GLX_SWAP_INTERVAL_EXT,
            &interval );

        return interval != 0;
    }

    void setVsyncEnabled( bool enabled ) override {
        // TODO: implement
    }

private:
    GLXFBConfig chooseFramebufferConfig() const {
        // TODO: figure out proper attributes
        const int attributes[] = {
            GLX_DOUBLEBUFFER, 1,
            0
        };

        int size;

        if( GLXFBConfig *configs = glXChooseFBConfig(
                _display, /* screen = */ 0, attributes, &size) ) {
            const GLXFBConfig result = *configs;
            XFree( configs );
            return result;
        }

        throw Exception() << "glXChooseFBConfig has failed";
    }

    ::Window getWindowHandle() const {
        return _outputWindow ?
            reinterpret_cast<::Window>( _outputWindow->getHandle() ) :
            reinterpret_cast<::Window>( _defaultWindow->getHandle() );
    }

    DisplayConnection _display;

    Window::Pointer _defaultWindow;
    Window::Pointer _outputWindow;

    GLXContext _context;
};

} // namespace

RenderingSystem* RenderingSystem::getInstance() {
    static const std::unique_ptr<RenderingSystemGlx> instance =
        std::make_unique<RenderingSystemGlx>();
    return instance.get();
}

}
