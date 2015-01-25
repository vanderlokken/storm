#include <storm/platform/x11/mouse_x11.h>

#include <map>
#include <memory>

namespace storm {

MouseX11::MouseX11() : _cursorPosition( {0, 0} ) {
    _eventListener.onButtonPress =
    _eventListener.onButtonRelease = [this]( const XIDeviceEvent &event ) {
        onButtonEvent( event );
    };

    _eventListener.onMovement = [this]( const XIDeviceEvent &event ) {
        const CursorPosition cursorPosition = {
            static_cast<int>( event.event_x ),
            static_cast<int>( event.event_y )
        };

        const Movement movement = {
            cursorPosition.x - _cursorPosition.x,
            cursorPosition.y - _cursorPosition.y
        };

        _cursorPosition = cursorPosition;

        if( movement.x || movement.y ) {
            // Wheel scrolling events are being filtered by the previous
            // condition.
            _observers.notify(
                &Observer::onCursorMovement, movement, cursorPosition );
        }
    };

    _eventListener.onRawMovement = [this]( const XIRawEvent &event ) {
        // TODO: ignore wheel scrolling events.
        const Movement movement = {
            static_cast<int>( event.raw_values[0] ),
            static_cast<int>( event.raw_values[1] )
        };
        _observers.notify( &Observer::onMovement, movement );
    };

    _eventListener.onEnter = [this]( const XIEnterEvent &event ) {
        _cursorPosition.x = static_cast<int>( event.event_x );
        _cursorPosition.y = static_cast<int>( event.event_y );
    };

    InputX11::getInstance()->setMouseEventListener( &_eventListener );
}

void MouseX11::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void MouseX11::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

bool MouseX11::isButtonPressed( Button ) const {
    throwNotImplemented();
}

bool MouseX11::getCursorVisibility() const {
    throwNotImplemented();
}

void MouseX11::setCursorVisibility( bool ) {
    throwNotImplemented();
}

bool MouseX11::getCursorMovementRestriction() const {
    throwNotImplemented();
}

void MouseX11::setCursorMovementRestriction( bool ) {
    throwNotImplemented();
}

Mouse::CursorPosition MouseX11::getCursorPosition() const {
    return _cursorPosition;
}

void MouseX11::onButtonEvent( const XIDeviceEvent &event ) {
    static const std::map<int, Button> buttonCodes = {
        {1, Button::Left},
        {2, Button::Middle},
        {3, Button::Right},
        {8, Button::SideFirst},
        {9, Button::SideSecond}
    };

    static const int scrollDown = 4;
    static const int scrollUp = 5;

    const unsigned int buttonCode = event.detail;

    if( buttonCodes.count(buttonCode) ) {
        switch( event.evtype ) {
        case XI_ButtonPress:
            _observers.notify(
                &Observer::onButtonPress, buttonCodes.at(buttonCode) );
            break;
        case XI_ButtonRelease:
            _observers.notify(
                &Observer::onButtonRelease, buttonCodes.at(buttonCode) );
            break;
        }
    } else if( buttonCode == scrollDown && event.evtype == XI_ButtonPress ) {
        _observers.notify( &Observer::onWheelRotation, -1 );
    } else if( buttonCode == scrollUp && event.evtype == XI_ButtonPress ) {
        _observers.notify( &Observer::onWheelRotation, 1 );
    }
}

Mouse* Mouse::getInstance() {
    static const std::unique_ptr<MouseX11> instance( new MouseX11 );
    return instance.get();
}

}
