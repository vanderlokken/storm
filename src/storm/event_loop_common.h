#pragma once

#include <storm/event_loop.h>
#include <storm/throw_exception.h>

namespace storm {

class EventLoopCommon : public EventLoop {
public:
    EventLoopCommon() :
        _running( false ),
        _eventsProcessed( false )
    {
    }

    virtual void run( const Callback &callback ) {
        storm_assert( callback );

        _running = true;

        while( _running ) {
            // This flag should be modified by the 'processEvents' method.
            _eventsProcessed = false;

            callback();

            if( !_eventsProcessed )
                processEvents();
        }
    }

    virtual void stop() {
        _running = false;
    }

protected:
    bool _running;
    bool _eventsProcessed;
};

}
