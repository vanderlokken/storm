#pragma once

#include <X11/Xlib.h>

#include <storm/noncopyable.h>
#include <storm/observer_list.h>
#include <storm/platform/x11/display_connection_x11.h>
#include <storm/platform/x11/event_loop_x11.h>
#include <storm/rendering_window.h>

namespace storm {

class RenderingWindowX11 : public RenderingWindow {
    NONCOPYABLE( RenderingWindowX11 );
public:
    static RenderingWindowX11* getInstance();

    explicit RenderingWindowX11( XDisplay *display );
    ~RenderingWindowX11();

    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual Dimensions getDimensions() const;

    virtual bool isActive() const;
    virtual bool isFullscreen() const;

    virtual void setWindowed( Dimensions windowDimensions );
    virtual void setFullscreen( FullscreenMode fullscreenMode );

    virtual const std::string& getTitle() const;
    virtual void setTitle( const std::string &title );

    Window getHandle() const;

    void addEventMask( unsigned long eventMask );

private:
    void installShutdownHandler();
    void installFocusHandlers();
    void installStateChangeHandlers();

    void setFullscreen( bool fullscreen );
    void setDimensionsConstraint( Dimensions dimensions );

    Window _handle;
    XDisplay *_display;

    bool _fullscreen;

    std::string _title;

    EventLoopX11::Listener _eventListener;

    ObserverList<Observer> _observers;
};

}
