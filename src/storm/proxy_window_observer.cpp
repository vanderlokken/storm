#include <storm/proxy_window_observer.h>

#include <algorithm>

namespace storm {

namespace {

using Observers = std::vector<std::weak_ptr<WindowObserver>>;

void removeExpiredObservers( Observers &observers ) {
    observers.erase(
        std::remove_if(
            observers.begin(),
            observers.end(),
            []( const std::weak_ptr<WindowObserver> &observer ) {
                return observer.expired();
            }),
        observers.end() );
}

template <class T, class... Args>
void runCallback( Observers &observers, T callback, Args&&... args )
{
    bool hasExpiredObservers = false;

    for( const std::weak_ptr<WindowObserver> &weakObserver : observers ) {
        if( const std::shared_ptr<WindowObserver> observer =
                weakObserver.lock() ) {
            if( (*observer).*callback ) {
                ((*observer).*callback)( std::forward<Args>(args)... );
            }
        } else {
            hasExpiredObservers = true;
        }
    }

    if( hasExpiredObservers ) {
        removeExpiredObservers( observers );
    }
}

} // namespace

ProxyWindowObserver::ProxyWindowObserver() :
    _observers( std::make_shared<Observers>() )
{
    update();
}

void ProxyWindowObserver::addObserver(
    std::weak_ptr<WindowObserver> observer )
{
    // The copy is required to correctly handle the situation when a new
    // observer is added from an observer callback.
    _observers = std::make_shared<Observers>( *_observers );
    _observers->push_back( std::move(observer) );
    update();
}

const WindowObserver* ProxyWindowObserver::operator -> () const {
    return &_observer;
}

void ProxyWindowObserver::update() {
    const std::shared_ptr<Observers> observers = _observers;

    _observer.onShutdownRequested = [=] {
        runCallback( *observers, &WindowObserver::onShutdownRequested );
    };
    _observer.onFocusReceived = [=] {
        runCallback( *observers, &WindowObserver::onFocusReceived );
    };
    _observer.onFocusLost = [=] {
        runCallback( *observers, &WindowObserver::onFocusLost );
    };
    _observer.onResized = [=] {
        runCallback( *observers, &WindowObserver::onResized );
    };
    _observer.onMouseMotion = [=]( IntVector2d delta ) {
        runCallback( *observers, &WindowObserver::onMouseMotion, delta );
    };
    _observer.onPointerMotion = [=]( IntVector2d delta ) {
        runCallback( *observers, &WindowObserver::onPointerMotion, delta );
    };
    _observer.onMouseButtonPressed = [=]( MouseButton button ) {
        runCallback(
            *observers, &WindowObserver::onMouseButtonPressed, button );
    };
    _observer.onMouseButtonReleased = [=]( MouseButton button ) {
        runCallback(
            *observers, &WindowObserver::onMouseButtonReleased, button );
    };
    _observer.onMouseWheelRotated = [=]( float delta ) {
        runCallback( *observers, &WindowObserver::onMouseWheelRotated, delta );
    };
    _observer.onKeyboardKeyPressed = [=]( KeyboardKey key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyPressed, key );
    };
    _observer.onKeyboardKeyRepeated = [=]( KeyboardKey key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyRepeated, key );
    };
    _observer.onKeyboardKeyReleased = [=]( KeyboardKey key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyReleased, key );
    };
    _observer.onCharacterInput = [=]( char32_t character ) {
        runCallback( *observers, &WindowObserver::onCharacterInput, character );
    };
}

}
