#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include "platform/ogl/RenderingSystemOgl.h"

namespace storm {

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    static std::shared_ptr<RenderingSystemWgl> getInstance();

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
