#pragma once

#include <X11/Xlib.h>

#include <storm/noncopyable.h>
#include <storm/rendering_window.h>

namespace storm {

class RenderingWindowX11 : public RenderingWindow {
    NONCOPYABLE( RenderingWindowX11 );
public:
    static std::shared_ptr<RenderingWindowX11> getInstance();

    virtual ~RenderingWindowX11();

    virtual Dimensions getDimensions() const noexcept;

    virtual bool isFullscreen() const noexcept;

    virtual void setWindowed( Dimensions windowDimensions );
    virtual void setFullscreen();

    Window getHandle() const noexcept;

private:
    RenderingWindowX11();

    Window _handle;
    Display *_display;

    Dimensions _dimensions;
    bool _fullscreen;
};

}
