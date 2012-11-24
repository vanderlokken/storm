#ifndef storm_EventHandlerVector_h
#define storm_EventHandlerVector_h

#include <vector>

#include "EventHandler.h"
#include "Noncopyable.h"

namespace storm {

template< class EventType > class EventHandlerVector {
    NONCOPYABLE( EventHandlerVector );
public:
    EventHandlerVector() { }
    
    void addEventHandler( const EventHandler<EventType>& );
    void operator () ( const EventType& );
    
private:
    std::unique_ptr< std::vector< EventHandler<EventType> > > _handlers;
};

template< class EventType > void EventHandlerVector<EventType>::addEventHandler( const EventHandler<EventType> &handler ) {
    if( !_handlers )
        _handlers.reset( new std::vector< EventHandler<EventType> > );
    
    _handlers->push_back( handler );
    
    return;
}

template< class EventType > void EventHandlerVector<EventType>::operator () ( const EventType &event ) {
    if( !_handlers )
        return;
    
    for( auto handler = _handlers->cbegin(); handler != _handlers->cend(); ++handler )
        (*handler)( event );
    
    return;
}

}

#endif