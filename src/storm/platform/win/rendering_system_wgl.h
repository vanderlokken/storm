#pragma once

#include <storm/platform/win/api_win.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

class DeviceContextHandle {
    NONCOPYABLE( DeviceContextHandle );
public:
    explicit DeviceContextHandle( HWND windowHandle );
    ~DeviceContextHandle();

    operator HDC () const {
        return _handle;
    }

private:
    HWND _windowHandle;
    HDC _handle;
};

class RenderingContextHandle {
    NONCOPYABLE( RenderingContextHandle );
public:
    explicit RenderingContextHandle( HGLRC handle );
    ~RenderingContextHandle();

    void install( HDC deviceContextHandle ) const;

    operator HGLRC () const {
        return _handle;
    }

private:
    HGLRC _handle;
};

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    static RenderingSystemWgl* getInstance();

    virtual void endFrameRendering();

private:
    explicit RenderingSystemWgl( HWND windowHandle );

    void selectPixelFormat();

    DeviceContextHandle _deviceContextHandle;
    std::unique_ptr<RenderingContextHandle> _renderingContextHandle;
};

}
