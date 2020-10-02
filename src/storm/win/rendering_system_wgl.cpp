#include <storm/win/api_win.h>

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/rendering_system_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

namespace {

class DeviceContextHandle {
public:
    explicit DeviceContextHandle( const Window& window ) :
        _handle( GetDC(static_cast<HWND>(window.getHandle())) )
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

        _handle = nullptr;
        std::swap( _handle, context._handle );

        return *this;
    }

    ~DeviceContextHandle() {
        if( _handle ) {
            ReleaseDC( WindowFromDC(_handle), _handle );
        }
    }

    operator HDC() const {
        return _handle;
    }

private:
    HDC _handle;
};

class GpuContextWgl final : public GpuContextOgl {
public:
    GpuContextWgl( HGLRC handle, Window::Pointer outputWindow ) :
        _outputWindow( std::move(outputWindow) ),
        _handle( handle )
    {
        activate();

        // 'wglGetProcAddress' doesn't return pointers to OpenGL 1.1 functions,
        // so we obtain these pointers from a shared library.
        const HMODULE moduleHandle = GetModuleHandle( L"opengl32.dll" );

        loadApiFunctions(
            [&](std::string_view name) {
                const PROC result = wglGetProcAddress( name.data() );

                return result ?
                    result : GetProcAddress( moduleHandle, name.data() );
            });
    }

    GpuContextWgl(
        const GpuContextWgl& ) = delete;
    GpuContextWgl& operator = (
        const GpuContextWgl& ) = delete;

    ~GpuContextWgl() {
        const DeviceContextHandle deviceContext( *_outputWindow );

        wglMakeCurrent( deviceContext, nullptr );
        wglDeleteContext( _handle );
    }

    void activate() const override {
        if( wglGetCurrentContext() != _handle ) {
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
        const DeviceContextHandle deviceContext( *_outputWindow );

        wglMakeCurrent( deviceContext, _handle );
    }

    Window::Pointer _outputWindow;
    HGLRC _handle;
};

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    RenderingSystemWgl() :
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
            std::dynamic_pointer_cast<GpuContextWgl>( getGpuContext() );

        context->setOutputWindow(
            _outputWindow ? _outputWindow : _defaultWindow );

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
        const auto context =
            std::dynamic_pointer_cast<GpuContextOgl>( getGpuContext() );

        if( context->getExtensionSupportStatus().wglExtSwapControl ) {
            const int intervalForVsync =
                context->getExtensionSupportStatus().wglExtSwapControlTear ?
                    -1 : 1;

            context->callUnchecked<WglSwapIntervalEXT>(
                _isVsyncEnabled ? intervalForVsync : 0 );
        }
    }

    Window::Pointer _defaultWindow;
    Window::Pointer _outputWindow;

    bool _isVsyncEnabled = true;
};

} // namespace

RenderingSystem::Pointer RenderingSystem::create() {
    return std::make_shared<RenderingSystemWgl>();
}

GpuContext::Pointer GpuContext::create() {
    const Window::Pointer window = Window::create();
    const DeviceContextHandle deviceContext( *window );

    const GpuContextWgl legacyContext(
        wglCreateContext(deviceContext), window );

    const int contextAttributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifndef NDEBUG
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
        0
    };

    if( !legacyContext.isFunctionAvailable<WglCreateContextAttribsARB>() ) {
        throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
    }

    const HGLRC coreContextHandle =
        legacyContext.callUnchecked<WglCreateContextAttribsARB>(
            deviceContext, nullptr, contextAttributes );

    if( !coreContextHandle ) {
        throw SystemRequirementsNotMet() << "OpenGL 3.3 is not supported";
    }

    return std::make_shared<GpuContextWgl>( coreContextHandle, window );
}

}
