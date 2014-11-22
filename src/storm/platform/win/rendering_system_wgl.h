#pragma once

#include <storm/platform/win/api_win.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

class RenderingSystemWgl : public RenderingSystemOgl {
public:
    static RenderingSystemWgl* getInstance();

    virtual ~RenderingSystemWgl();

    virtual void endFrameRendering();

private:
    RenderingSystemWgl();

    HWND _renderingWindowHandle;
    HDC _deviceContextHandle;
    HGLRC _renderingContextHandle;
};

}
