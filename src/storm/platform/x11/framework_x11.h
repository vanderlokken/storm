#pragma once

#include <map>

#include <X11/Xlib.h>

#include <storm/framework.h>
#include <storm/noncopyable.h>

namespace storm {

class FrameworkX11 : public Framework {
    NONCOPYABLE( FrameworkX11 );
public:
    typedef std::function<void (const XEvent&)> EventCallback;

    FrameworkX11();
    ~FrameworkX11();

    static FrameworkX11* getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

    virtual void processInputEvents() {}

    Display* getDisplayHandle();

    void setEventCallback( int eventType, const EventCallback &eventCallback );
    void removeEventCallback( int eventType );

private:
    Display *_display;

    std::map<int, EventCallback> _eventCallbacks;
};

}
