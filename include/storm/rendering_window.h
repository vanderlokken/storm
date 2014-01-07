#pragma once

#include <storm/dimensions.h>
#include <storm/noexcept.h>

namespace storm {

class RenderingWindow {
public:
    static RenderingWindow* getInstance();

    virtual ~RenderingWindow() { }

    virtual Dimensions getDimensions() const noexcept = 0;

    virtual bool isActive() const noexcept = 0;
    virtual bool isFullscreen() const noexcept = 0;

    virtual void setWindowed( Dimensions windowDimensions ) = 0;
    virtual void setFullscreen() = 0;
};

}