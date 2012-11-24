#ifndef storm_RenderingWindowX11_h
#define storm_RenderingWindowX11_h

#include <X11/Xlib.h>

#include "Noncopyable.h"
#include "RenderingWindow.h"

namespace storm {

class RenderingWindowX11 : public RenderingWindow {
    NONCOPYABLE( RenderingWindowX11 );
public:
    static std::shared_ptr<RenderingWindowX11> getInstance();

    virtual ~RenderingWindowX11() noexcept;

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

#endif
