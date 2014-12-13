#pragma once

#include <functional>

#include <storm/dimensions.h>
#include <storm/display.h>

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

    struct FullscreenMode {
        bool custom;
        Display::Mode mode;
    };

    static RenderingWindow* getInstance();

    virtual ~RenderingWindow() {}

    virtual void addObserver( const Observer* ) = 0;
    virtual void removeObserver( const Observer* ) = 0;

    virtual Dimensions getDimensions() const = 0;

    virtual bool isActive() const = 0;
    virtual bool isFullscreen() const = 0;

    virtual void setWindowed( Dimensions windowDimensions ) = 0;
    // With default arguments sets so-called 'windowed fullscreen' mode which
    // doesn't change display mode. When custom display mode is specified, every
    // time the rendering window receives focus, sets custom display mode,
    // and every time the rendering window loses focus, restores default display
    // mode. When specified custom diplay mode is not supported falls back to
    // the windowed fullscreen mode.
    virtual void setFullscreen( FullscreenMode fullscreenMode = {} ) = 0;
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
