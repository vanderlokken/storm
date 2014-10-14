#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <storm/noncopyable.h>
#include <storm/observer_list.h>
#include <storm/rendering_window.h>

namespace storm {

class RenderingWindowWin : public RenderingWindow {
    NONCOPYABLE( RenderingWindowWin );
public:
    static RenderingWindowWin* getInstance();

    virtual ~RenderingWindowWin();

    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual Dimensions getDimensions() const;

    virtual bool isActive() const;
    virtual bool isFullscreen() const;

    virtual void setWindowed( Dimensions windowDimensions );
    virtual void setFullscreen();

    HWND getHandle() const;

private:
    RenderingWindowWin();

    static LRESULT CALLBACK windowProcedure( HWND, UINT, WPARAM, LPARAM );

    HWND _handle;

    Dimensions _dimensions;
    bool _fullscreen;

    ObserverList<Observer> _observers;
};

}
