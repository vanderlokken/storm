#pragma once

#include <map>

#include <X11/Xlib.h>

#include <storm/event_loop_common.h>
#include <storm/noncopyable.h>
#include <storm/observer_list.h>

namespace storm {

class EventLoopX11 : public EventLoopCommon {
    NONCOPYABLE( EventLoopX11 );
public:
    struct Listener {
        Listener() {
            EventLoopX11::getInstance()->addListener( this );
        }
        ~Listener() {
            EventLoopX11::getInstance()->removeListener( this );
        }
        Listener( const Listener& ) = delete;
        Listener& operator = ( const Listener& ) = delete;

        typedef int EventType;
        typedef std::function<void (const XEvent&)> Callback;

        std::map<EventType, Callback> onEvent;
    };

    EventLoopX11( Display *display );
    static EventLoopX11* getInstance();

    virtual void processEvents();

private:
    void addListener( const Listener* );
    void removeListener( const Listener* );

    Display *_display;

    ObserverList<Listener> _listeners;
};

}
