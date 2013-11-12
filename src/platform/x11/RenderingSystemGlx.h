#pragma once

#include "platform/ogl/CoreTypesOgl.h"
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

#include "platform/ogl/RenderingSystemOgl.h"

namespace storm {

class RenderingSystemGlx : public RenderingSystemOgl {
public:
    static std::shared_ptr<RenderingSystemGlx> getInstance();

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
