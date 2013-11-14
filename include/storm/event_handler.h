#pragma once

#include <functional>
#include <memory>

namespace storm {

template< class EventType > class EventHandler {
public:
    EventHandler( void (*handler)(const EventType&) )
        : _handler( handler ), _registration( getPermanentRegistration() ) { }

    EventHandler( const std::function<void (const EventType&)> &handler )
        : _handler( handler ), _registration( getPermanentRegistration() ) { }

    template< class HandlerClass > EventHandler(
        void (HandlerClass::*handlerMethod)(const EventType&), HandlerClass *handlerInstance );

    template< class HandlerClass > EventHandler(
        void (HandlerClass::*handlerMethod)(const EventType&), const std::shared_ptr<HandlerClass> &handlerInstance );

    template< class HandlerClass > EventHandler(
        void (HandlerClass::*handlerMethod)(const EventType&), HandlerClass *handlerInstance, const std::shared_ptr<void> &registration );

    void operator () ( const EventType &event ) const { if( !isExpired() ) _handler( event ); }

    bool isExpired() const { return _registration.expired(); }

private:
    static std::shared_ptr< void > getPermanentRegistration() {
        static const std::shared_ptr< char > registration = std::make_shared< char >();
        return registration;
    }

    std::function< void (const EventType&) > _handler;
    std::weak_ptr< void > _registration;
};

template< class EventType > template< class HandlerClass > EventHandler<EventType>::EventHandler(
    void (HandlerClass::*handlerMethod)(const EventType&), HandlerClass *handlerInstance )
    : _handler( std::bind(handlerMethod, handlerInstance, std::placeholders::_1) ), _registration( getPermanentRegistration() ) { }

template< class EventType > template< class HandlerClass > EventHandler<EventType>::EventHandler(
    void (HandlerClass::*handlerMethod)(const EventType&), const std::shared_ptr<HandlerClass> &handlerInstance )
    : _handler( std::bind(handlerMethod, handlerInstance, std::placeholders::_1) ), _registration( handlerInstance ) { }

template< class EventType > template< class HandlerClass > EventHandler<EventType>::EventHandler(
    void (HandlerClass::*handlerMethod)(const EventType&), HandlerClass *handlerInstance, const std::shared_ptr<void> &registration )
    : _handler( std::bind(handlerMethod, handlerInstance, std::placeholders::_1) ), _registration( registration ) { }

}
