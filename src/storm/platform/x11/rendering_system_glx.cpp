#include <storm/platform/ogl/rendering_system_ogl.h>

#include <string_view>

#include <storm/exception.h>
#include <storm/platform/ogl/api_ogl.h>

// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

namespace storm {

namespace {

class DisplayConnection {
public:
    DisplayConnection() :
        _display( XOpenDisplay(nullptr) )
    {
        if( !_display ) {
            throw SystemRequirementsNotMet() << "An X server is unavailable";
        }
    }

    ~DisplayConnection() {
        XCloseDisplay( _display );
    }

    DisplayConnection(
        const DisplayConnection& ) = delete;
    DisplayConnection& operator = (
        const DisplayConnection& ) = delete;

    operator Display* () const {
        return _display;
    }

private:
    Display *_display;
};

class RenderingSystemGlx : public RenderingSystemOgl {
public:
    RenderingSystemGlx() :
        _defaultWindow( Window::create() )
    {
        if( getGlxSupportStatus().ARB_create_context ) {
            _glXCreateContextAttribsARB =
                loadExtensionFunction<PFNGLXCREATECONTEXTATTRIBSARBPROC>(
                    "glXCreateContextAttribsARB" );
        }

        if( getGlxSupportStatus().EXT_swap_control ) {
            _glXSwapIntervalEXT =
                loadExtensionFunction<PFNGLXSWAPINTERVALEXTPROC>(
                    "glXSwapIntervalEXT" );
        }

        if( getGlxSupportStatus().MESA_swap_control ) {
            _glXSwapIntervalMESA =
                loadExtensionFunction<PFNGLXSWAPINTERVALMESAPROC>(
                    "glXSwapIntervalMESA" );
        }

        if( !_glXCreateContextAttribsARB ) {
            throw SystemRequirementsNotMet() << "Required OpenGL extension"
                "'GLX_ARB_create_context' is not supported";
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

        _context = _glXCreateContextAttribsARB(
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

        if( _outputWindow ) {
            applyVsyncSettings();
        }
    }

    void presentBackbuffer() override {
        glXSwapBuffers( _display, getWindowHandle() );
    }

    bool isVsyncEnabled() const override {
        return _isVsyncEnabled;
    }

    void setVsyncEnabled( bool enabled ) override {
        _isVsyncEnabled = enabled;

        if( _outputWindow ) {
            applyVsyncSettings();
        }
    }

private:
    template <class FuntionPointer>
    static FuntionPointer loadExtensionFunction(
        std::string_view functionName )
    {
        return reinterpret_cast<FuntionPointer>(
            glXGetProcAddress(
                reinterpret_cast<const unsigned char*>(functionName.data())) );
    }

    GLXFBConfig chooseFramebufferConfig() const {
        const int attributes[] = {
            GLX_DOUBLEBUFFER, 1,
            GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB, 1,
            0
        };

        int size;

        if( GLXFBConfig *configs = glXChooseFBConfig(
                _display, XDefaultScreen(_display), attributes, &size) ) {
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

    void applyVsyncSettings() const {
        if( _glXSwapIntervalMESA ) {
            _glXSwapIntervalMESA( _isVsyncEnabled ? 1 : 0 );
        } else if( _glXSwapIntervalEXT ) {
            _glXSwapIntervalEXT(
                _display, getWindowHandle(), _isVsyncEnabled ? 1 : 0 );
        }
    }

    DisplayConnection _display;

    Window::Pointer _defaultWindow;
    Window::Pointer _outputWindow;

    GLXContext _context = {};

    bool _isVsyncEnabled = true;

    PFNGLXCREATECONTEXTATTRIBSARBPROC _glXCreateContextAttribsARB = nullptr;
    PFNGLXSWAPINTERVALEXTPROC _glXSwapIntervalEXT = nullptr;
    PFNGLXSWAPINTERVALMESAPROC _glXSwapIntervalMESA = nullptr;
};

} // namespace

RenderingSystem* RenderingSystem::getInstance() {
    static const std::unique_ptr<RenderingSystemGlx> instance =
        std::make_unique<RenderingSystemGlx>();
    return instance.get();
}

}
