#pragma once

#include <storm/noncopyable.h>
#include <storm/platform/ogl/api_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/x11/display_connection_x11.h>

// To prevent <GL/gl.h> inclusion. glcorearb.h is used instead.
#define __gl_h_

#include <GL/glx.h>
#include <X11/Xlib.h>

namespace storm {

class RenderingSystemGlx : public RenderingSystemOgl {
    NONCOPYABLE( RenderingSystemGlx );
public:
    static RenderingSystemGlx* getInstance();

    RenderingSystemGlx( XDisplay *display, Window window );
    ~RenderingSystemGlx();

    virtual void beginFrameRendering();
    virtual void endFrameRendering();

    virtual bool isVsyncEnabled() const;
    virtual void setVsyncEnabled( bool enabled );

private:
    XDisplay *_display;
    Window _window;

    GLXContext _context;
};

}
