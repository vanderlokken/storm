#pragma once

#include <storm/dimensions.h>

namespace storm {

class RenderingWindow {
public:
    static RenderingWindow* getInstance();

    virtual ~RenderingWindow() { }

    virtual Dimensions getDimensions() const = 0;

    virtual bool isActive() const = 0;
    virtual bool isFullscreen() const = 0;

    virtual void setWindowed( Dimensions windowDimensions ) = 0;
    virtual void setFullscreen() = 0;
};

}
