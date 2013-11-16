#pragma once

#include <storm/event_handler.h>
#include <storm/noexcept.h>

namespace storm {

class Mouse {
public:
    enum class Button {
        Left,
        Right,
        Middle,
        SideFirst,
        SideSecond
    };

    struct ButtonEvent {
        Button button;
    };

    struct ButtonPressEvent : public ButtonEvent { };
    struct ButtonReleaseEvent : public ButtonEvent { };

    struct WheelRotationEvent {
        int distance;
    };

    struct MovementEvent {
        int x;
        int y;
    };

    static Mouse* getInstance();

    virtual ~Mouse() { }

    virtual void addEventHandler( const EventHandler<ButtonPressEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<ButtonReleaseEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<WheelRotationEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<MovementEvent>& ) = 0;

    virtual bool isButtonPressed( Button ) const noexcept = 0;

    virtual bool getCursorVisibility() const noexcept = 0;
    virtual void setCursorVisibility( bool ) noexcept = 0;

    virtual bool getCursorMovementRestriction() const noexcept = 0;
    virtual void setCursorMovementRestriction( bool ) noexcept = 0;
};

}
