#pragma once

#include <storm/event_handler.h>

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

    // MovementEvent respresents raw mouse movement events. It's parameters are
    // unaffected by system mouse sensitivity settings.

    struct MovementEvent {
        int deltaX;
        int deltaY;
    };

    struct CursorMovementEvent {
        int x;
        int y;
        int deltaX;
        int deltaY;
    };

    struct CursorPosition {
        int x;
        int y;
    };

    static Mouse* getInstance();

    virtual ~Mouse() { }

    virtual void addEventHandler( const EventHandler<ButtonPressEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<ButtonReleaseEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<WheelRotationEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<MovementEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<CursorMovementEvent>& ) = 0;

    virtual bool isButtonPressed( Button ) const = 0;

    virtual bool getCursorVisibility() const = 0;
    virtual void setCursorVisibility( bool ) = 0;

    virtual bool getCursorMovementRestriction() const = 0;
    virtual void setCursorMovementRestriction( bool ) = 0;

    virtual CursorPosition getCursorPosition() const = 0;
};

}
