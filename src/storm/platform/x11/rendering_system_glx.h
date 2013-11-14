#pragma once

#include <storm/platform/ogl/core_types_ogl.h>
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

class RenderingSystemGlx : public RenderingSystemOgl {
public:
    static RenderingSystemGlx* getInstance();

    virtual ~RenderingSystemGlx();

    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual void setColorBufferFormat( ColorBufferFormat );
    virtual void setDepthBufferFormat( DepthBufferFormat );

private:
    RenderingSystemGlx();

    Display *_display;
    Window _window;

    GLXContext _context;
};

}
