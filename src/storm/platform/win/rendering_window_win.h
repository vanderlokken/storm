#pragma once

#include <storm/noncopyable.h>
#include <storm/observer_list.h>
#include <storm/platform/win/api_win.h>
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
    virtual void setWindowedMaximized();
    virtual void setFullscreen( FullscreenMode fullscreenMode );

    virtual const std::string& getTitle() const;
    virtual void setTitle( const std::string &title );

    HWND getHandle() const;

private:
    RenderingWindowWin();

    static LRESULT CALLBACK windowProcedure( HWND, UINT, WPARAM, LPARAM );

    HWND _handle;

    Dimensions _dimensions;
    bool _fullscreen;
    FullscreenMode _fullscreenMode;

    std::string _title;

    ObserverList<Observer> _observers;
};

}
