#include <storm/ogl/rendering_system_ogl.h>

#include <string_view>

#include <storm/exception.h>
#include <storm/ogl/api_functions_ogl.h>
#include <storm/ogl/gpu_context_ogl.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace storm {

namespace {

class DisplayConnection {
public:
    using Pointer = std::shared_ptr<DisplayConnection>;

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

GLXFBConfig chooseFramebufferConfig( Display* display ) {
    const int attributes[] = {
        GLX_DOUBLEBUFFER, 1,
        GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB, 1,
        0
    };

    int size;

    if( GLXFBConfig *configs = glXChooseFBConfig(
            display, XDefaultScreen(display), attributes, &size) ) {
        const GLXFBConfig result = *configs;
        XFree( configs );
        return result;
    }

    throw Exception() << "glXChooseFBConfig has failed";
}

class GpuContextGlx : public GpuContextOgl {
public:
    GpuContextGlx(
            GLXContext context, DisplayConnection::Pointer display ) :
        _display( std::move(display) ),
        _outputWindow( Window::create() ),
        _context( context )
    {
        activate();

        loadApiFunctions(
            [](std::string_view name) {
                return reinterpret_cast<void*>(
                    glXGetProcAddress(
                        reinterpret_cast<const unsigned char*>(name.data())) );
            });
    }

    ~GpuContextGlx() {
        glXMakeCurrent( *_display, None, 0 );
        glXDestroyContext( *_display, _context );
    }

    DisplayConnection::Pointer getDisplayConnection() const {
        return _display;
    }

    void activate() const override {
        if( glXGetCurrentContext() != _context ) {
            doActivate();
        }
    }

    void setOutputWindow( Window::Pointer outputWindow ) {
        if( _outputWindow != outputWindow ) {
            _outputWindow = std::move( outputWindow );
            assertThreadCompatibility();
            doActivate();
        }
    }

private:
    void doActivate() const {
        glXMakeCurrent(
            *_display,
            reinterpret_cast<::Window>(_outputWindow->getHandle()),
            _context );
    }

    DisplayConnection::Pointer _display;
    Window::Pointer _outputWindow;
    GLXContext _context = {};
};

class RenderingSystemGlx : public RenderingSystemOgl {
public:
    RenderingSystemGlx() :
        _display(
            std::dynamic_pointer_cast<GpuContextGlx>(getGpuContext())
                ->getDisplayConnection() ),
        _defaultWindow( Window::create() )
    {
        setOutputWindow( nullptr );

        initialize();
    }

    Window::Pointer getOutputWindow() const override {
        return _outputWindow;
    }

    void setOutputWindow( Window::Pointer window ) override {
        _outputWindow = std::move( window );

        const auto context =
            std::dynamic_pointer_cast<GpuContextGlx>( getGpuContext() );

        context->setOutputWindow(
            _outputWindow ? _outputWindow : _defaultWindow );

        if( _outputWindow ) {
            applyVsyncSettings();
        }
    }

    void presentBackbuffer() override {
        glXSwapBuffers( *_display, getWindowHandle() );
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
    ::Window getWindowHandle() const {
        return _outputWindow ?
            reinterpret_cast<::Window>( _outputWindow->getHandle() ) :
            reinterpret_cast<::Window>( _defaultWindow->getHandle() );
    }

    void applyVsyncSettings() const {
        const auto context =
            std::dynamic_pointer_cast<GpuContextOgl>( getGpuContext() );

        if( context->isFunctionAvailable<GlXSwapIntervalMESA>() ) {
            context->callUnchecked<GlXSwapIntervalMESA>(
                _isVsyncEnabled ? 1 : 0 );
        } else if( context->isFunctionAvailable<GlXSwapIntervalEXT>() ) {
            context->callUnchecked<GlXSwapIntervalEXT>(
                *_display, getWindowHandle(), _isVsyncEnabled ? 1 : 0 );
        }
    }

    DisplayConnection::Pointer _display;

    Window::Pointer _defaultWindow;
    Window::Pointer _outputWindow;

    bool _isVsyncEnabled = true;
};

} // namespace

RenderingSystem::Pointer RenderingSystem::create() {
    return std::make_shared<RenderingSystemGlx>();
}

GpuContext::Pointer GpuContext::create() {
    const auto display = std::make_shared<DisplayConnection>();

    const GpuContextGlx legacyContext(
        glXCreateContext(
            *display,
            glXGetVisualFromFBConfig(
                *display, chooseFramebufferConfig(*display)),
            nullptr, // shareListContext
            true     // useDirectRendering
        ),
        display );

    const int contextAttributes[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
#endif
        0
    };

    if( !legacyContext.isFunctionAvailable<GlXCreateContextAttribsARB>() ) {
        throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
    }

    const GLXContext context =
        legacyContext.callUnchecked<GlXCreateContextAttribsARB>(
            *display,
            chooseFramebufferConfig(*display),
            nullptr, // shareListContext
            true,    // useDirectRendering
            contextAttributes );

    if( !context ) {
        throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
    }

    return std::make_shared<GpuContextGlx>( context, display );
}

}
