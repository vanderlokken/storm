#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <storm/noncopyable.h>
#include <storm/rendering_window.h>

namespace storm {

class RenderingWindowWin : public RenderingWindow {
    NONCOPYABLE( RenderingWindowWin );
public:
    static std::shared_ptr<RenderingWindowWin> getInstance();

    virtual ~RenderingWindowWin();

    virtual Dimensions getDimensions() const noexcept;

    virtual bool isActive() const noexcept;
    virtual bool isFullscreen() const noexcept;

    virtual void setWindowed( Dimensions windowDimensions );
    virtual void setFullscreen();

    HWND getHandle() const noexcept;

private:
    RenderingWindowWin();

    static LRESULT CALLBACK windowProcedure( HWND, UINT, WPARAM, LPARAM ) noexcept;

    HWND _handle;
    Dimensions _dimensions;
    bool _fullscreen;
};

}
