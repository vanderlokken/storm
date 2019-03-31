#include <storm/platform/win/api_win.h>

#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/throw_exception.h>

// Unpacked from contrib/wglext-*.tar.gz
#include <GL/wglext.h>

namespace storm {

namespace {

class DeviceContextHandle {
public:
    explicit DeviceContextHandle( const Window& window ) :
        _windowHandle( static_cast<HWND>(window.getHandle()) ),
        _contextHandle( GetDC(_windowHandle) )
    {
    }

    DeviceContextHandle(
        const DeviceContextHandle& ) = delete;
    DeviceContextHandle& operator = (
        const DeviceContextHandle& ) = delete;

    DeviceContextHandle( DeviceContextHandle &&context ) {
        *this = std::move( context );
    }

    DeviceContextHandle& operator = ( DeviceContextHandle &&context ) {
        this->~DeviceContextHandle();

        _contextHandle = context._contextHandle;
        _windowHandle = context._windowHandle;

        context._contextHandle = nullptr;

        return *this;
    }

    ~DeviceContextHandle() {
        if( _contextHandle ) {
            ReleaseDC( _windowHandle, _contextHandle );
        }
    }

    operator HDC() const {
        return _contextHandle;
    }

private:
    HWND _windowHandle;
    HDC _contextHandle;
};

class RenderingContextHandle {
public:
    explicit RenderingContextHandle( HGLRC handle ) :
        _handle( handle )
    {
    }

    RenderingContextHandle(
        const RenderingContextHandle& ) = delete;
    RenderingContextHandle& operator = (
        const RenderingContextHandle& ) = delete;

    ~RenderingContextHandle() {
        wglDeleteContext( _handle );
    }

    operator HGLRC() const {
        return _handle;
    }

private:
    HGLRC _handle;
};

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    RenderingSystemWgl() :
        _defaultWindow( Window::create() )
    {
        const DeviceContextHandle deviceContext = getDeviceContext();

        const RenderingContextHandle renderingContext(
            wglCreateContext(deviceContext) );

        wglMakeCurrent( deviceContext, renderingContext );

        if( getWglSupportStatus().ARB_create_context ) {
            _wglCreateContextAttribsARB =
                reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
                    wglGetProcAddress("wglCreateContextAttribsARB") );
        }
        if( getWglSupportStatus().EXT_swap_control ) {
            _wglSwapIntervalEXT =
                reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(
                    wglGetProcAddress("wglSwapIntervalEXT") );
        }

        if( !getWglSupportStatus().ARB_extensions_string ) {
            throw SystemRequirementsNotMet() << "Required OpenGL extension"
                "'WGL_ARB_extensions_string' is not supported";
        }
        if( !_wglCreateContextAttribsARB ) {
            throw SystemRequirementsNotMet() << "Required OpenGL extension"
                "'WGL_ARB_create_context' is not supported";
        }

        const int contextAttributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    #ifndef NDEBUG
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
    #endif
            0
        };

        _renderingContext = std::make_unique<RenderingContextHandle>(
            _wglCreateContextAttribsARB(deviceContext, 0, contextAttributes) );

        if( !*_renderingContext ) {
            throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
        }

        wglMakeCurrent( deviceContext, *_renderingContext );

        initialize();
    }

    Window::Pointer getOutputWindow() const override {
        return _outputWindow;
    }

    void setOutputWindow( Window::Pointer window ) override {
        _outputWindow = std::move( window );

        const DeviceContextHandle deviceContext = getDeviceContext();
        wglMakeCurrent( deviceContext, *_renderingContext );

        if( _outputWindow ) {
            applyVsyncSettings();
        }
    }

    void presentBackbuffer() override {
        const DeviceContextHandle deviceContext = getDeviceContext();
        SwapBuffers( deviceContext );
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
    DeviceContextHandle getDeviceContext() const {
        return DeviceContextHandle(
            _outputWindow ? *_outputWindow : *_defaultWindow );
    }

    void applyVsyncSettings() const {
        if( _wglSwapIntervalEXT ) {
            if( getWglSupportStatus().EXT_swap_control_tear ) {
                _wglSwapIntervalEXT( _isVsyncEnabled ? -1 : 0 );
            } else {
                _wglSwapIntervalEXT( _isVsyncEnabled ? 1 : 0 );
            }
        }
    }

    Window::Pointer _defaultWindow;
    Window::Pointer _outputWindow;

    bool _isVsyncEnabled = true;

    PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribsARB = nullptr;
    PFNWGLSWAPINTERVALEXTPROC _wglSwapIntervalEXT = nullptr;

    std::unique_ptr<RenderingContextHandle> _renderingContext;
};

} // namespace

RenderingSystem* RenderingSystem::getInstance() {
    static const std::unique_ptr<RenderingSystemWgl> instance =
        std::make_unique<RenderingSystemWgl>();
    return instance.get();
}

}
