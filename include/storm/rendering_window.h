#pragma once

#include <functional>

#include <storm/dimensions.h>

namespace storm {

class RenderingWindow {
public:
    struct Observer {
        std::function<void()> onShutdown;
        std::function<void()> onFocusIn;
        std::function<void()> onFocusOut;
        std::function<void()> onFolding;
        std::function<void()> onUnfolding;
    };

    static RenderingWindow* getInstance();

    virtual ~RenderingWindow() {}

    virtual void addObserver( const Observer* ) = 0;
    virtual void removeObserver( const Observer* ) = 0;

    virtual Dimensions getDimensions() const = 0;

    virtual bool isActive() const = 0;
    virtual bool isFullscreen() const = 0;

    virtual void setWindowed( Dimensions windowDimensions ) = 0;
    virtual void setFullscreen() = 0;
};

struct ScopedRenderingWindowObserver : RenderingWindow::Observer {
    ScopedRenderingWindowObserver() {
        RenderingWindow::getInstance()->addObserver( this );
    }
    ~ScopedRenderingWindowObserver() {
        RenderingWindow::getInstance()->removeObserver( this );
    }
    ScopedRenderingWindowObserver(
        const ScopedRenderingWindowObserver& ) = delete;
    ScopedRenderingWindowObserver& operator = (
        const ScopedRenderingWindowObserver& ) = delete;
};

}
