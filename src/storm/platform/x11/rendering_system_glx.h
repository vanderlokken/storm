#pragma once

#include <storm/noncopyable.h>
#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

namespace storm {

class RenderingSystemGlx : public RenderingSystemOgl {
    NONCOPYABLE( RenderingSystemGlx );
public:
    static RenderingSystemGlx* getInstance();

    RenderingSystemGlx( Display *display, Window window );
    ~RenderingSystemGlx();

    virtual void beginFrameRendering();
    virtual void endFrameRendering();

private:
    Display *_display;
    Window _window;

    GLXContext _context;
};

}
