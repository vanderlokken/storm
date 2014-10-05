#pragma once

#include <X11/Xlib.h>

#include <storm/noncopyable.h>
#include <storm/rendering_window.h>

namespace storm {

class RenderingWindowX11 : public RenderingWindow {
    NONCOPYABLE( RenderingWindowX11 );
public:
    static RenderingWindowX11* getInstance();

    RenderingWindowX11( Display *display );
    ~RenderingWindowX11();

    virtual Dimensions getDimensions() const;

    virtual bool isActive() const;
    virtual bool isFullscreen() const;

    virtual void setWindowed( Dimensions windowDimensions );
    virtual void setFullscreen();

    Window getHandle() const;

private:
    Window _handle;
    Display *_display;

    Dimensions _dimensions;
    bool _fullscreen;
};

}
