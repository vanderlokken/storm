#pragma once

#include <memory>

#include "EventHandler.h"
#include "Noexcept.h"

namespace storm {

class Mouse {
public:
    enum Button {
        ButtonLeft,
        ButtonRight,
        ButtonMiddle,
        ButtonSideFirst,
        ButtonSideSecond
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

    static std::shared_ptr<Mouse> getInstance();

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
