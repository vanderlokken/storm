#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    static RenderingSystemWgl* getInstance();

    virtual ~RenderingSystemWgl();

    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual void setColorBufferFormat( ColorBufferFormat );
    virtual void setDepthBufferFormat( DepthBufferFormat );

private:
    RenderingSystemWgl();

    HWND _renderingWindowHandle;
    HDC _deviceContextHandle;
    HGLRC _renderingContextHandle;
};

}