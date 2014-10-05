#include <storm/platform/x11/event_loop_x11.h>

#include <memory>

#include <storm/platform/x11/display_connection_x11.h>

namespace storm {

EventLoopX11::EventLoopX11( Display *display ) :
    _display( display )
{
}

void EventLoopX11::processEvents() {
    const int pendingEventCount = ::XPending( _display );

    for( int i = 0; i < pendingEventCount; ++i ) {
        XEvent event;
        ::XNextEvent( _display, &event );

        _listeners.forEach( [&event]( const Listener &listener ) {
            const auto iterator = listener.onEvent.find( event.type );
            if( iterator != listener.onEvent.end() )
                iterator->second( event );
        });
    }

    _eventsProcessed = true;
}

void EventLoopX11::addListener( const Listener *listener ) {
    _listeners.add( listener );
}

void EventLoopX11::removeListener( const Listener *listener ) {
    _listeners.remove( listener );
}

EventLoopX11* EventLoopX11::getInstance() {
    static const std::unique_ptr<EventLoopX11> instance(
        new EventLoopX11(getDisplayHandleX11()) );
    return instance.get();
}

EventLoop* EventLoop::getInstance() {
    return EventLoopX11::getInstance();
}

}
