#ifndef storm_RenderingWindow_h
#define storm_RenderingWindow_h

#include <memory>

#include "Dimensions.h"
#include "Noexcept.h"

namespace storm {

class RenderingWindow {
public:
    static std::shared_ptr<RenderingWindow> getInstance();

    virtual ~RenderingWindow() noexcept { }

    virtual Dimensions getDimensions() const noexcept = 0;

    virtual bool isActive() const noexcept = 0;
    virtual bool isFullscreen() const noexcept = 0;

    virtual void setWindowed( Dimensions windowDimensions ) = 0;
    virtual void setFullscreen() = 0;
};

}

#endif