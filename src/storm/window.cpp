#include <storm/window.h>

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
}

ProxyWindowObserver::operator WindowObserver() const {
    const std::shared_ptr<Observers> observers = _observers;

    WindowObserver windowObserver;

    windowObserver.onShutdownRequested = [=] {
        runCallback( *observers, &WindowObserver::onShutdownRequested );
    };
    windowObserver.onFocusReceived = [=] {
        runCallback( *observers, &WindowObserver::onFocusReceived );
    };
    windowObserver.onFocusLost = [=] {
        runCallback( *observers, &WindowObserver::onFocusLost );
    };
    windowObserver.onResized = [=] {
        runCallback( *observers, &WindowObserver::onResized );
    };
    windowObserver.onMouseMotion = [=]( IntVector2d delta ) {
        runCallback( *observers, &WindowObserver::onMouseMotion, delta );
    };
    windowObserver.onMouseButtonPressed = [=]( Mouse::Button button ) {
        runCallback(
            *observers, &WindowObserver::onMouseButtonPressed, button );
    };
    windowObserver.onMouseButtonReleased = [=]( Mouse::Button button ) {
        runCallback(
            *observers, &WindowObserver::onMouseButtonReleased, button );
    };
    windowObserver.onMouseWheelRotated = [=]( float delta ) {
        runCallback( *observers, &WindowObserver::onMouseWheelRotated, delta );
    };
    windowObserver.onPointerMotion = [=]( IntVector2d delta ) {
        runCallback( *observers, &WindowObserver::onPointerMotion, delta );
    };
    windowObserver.onKeyboardKeyPressed = [=]( Keyboard::Key key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyPressed, key );
    };
    windowObserver.onKeyboardKeyRepeated = [=]( Keyboard::Key key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyRepeated, key );
    };
    windowObserver.onKeyboardKeyReleased = [=]( Keyboard::Key key ) {
        runCallback( *observers, &WindowObserver::onKeyboardKeyReleased, key );
    };

    return windowObserver;
}

void ProxyWindowObserver::addObserver(
    std::weak_ptr<WindowObserver> observer )
{
    _observers->push_back( std::move(observer) );
}

}
