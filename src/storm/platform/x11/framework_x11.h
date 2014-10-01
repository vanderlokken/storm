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

    static FrameworkX11* getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

    virtual void processInputEvents() {}

    virtual void setEventCallback(
        int eventType, const EventCallback &eventCallback );
    virtual void removeEventCallback(
        int eventType );

private:
    FrameworkX11();

    Display *_display;

    std::map<int, EventCallback> _eventCallbacks;
};

}
