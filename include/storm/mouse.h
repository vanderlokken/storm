#pragma once

#include <functional>

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

    struct Movement {
        int x;
        int y;
    };

    struct CursorPosition {
        int x;
        int y;
    };

    struct Observer {
        std::function<void(Button)> onButtonPress;
        std::function<void(Button)> onButtonRelease;
        std::function<void(int)> onWheelRotation;
        std::function<void(Movement)> onMovement;
        std::function<void(Movement, CursorPosition)> onCursorMovement;
    };

    static Mouse* getInstance();

    virtual ~Mouse() {}

    virtual void addObserver( const Observer* ) = 0;
    virtual void removeObserver( const Observer* ) = 0;

    virtual bool isButtonPressed( Button ) const = 0;

    virtual bool getCursorVisibility() const = 0;
    virtual void setCursorVisibility( bool ) = 0;

    virtual bool getCursorMovementRestriction() const = 0;
    virtual void setCursorMovementRestriction( bool ) = 0;

    virtual CursorPosition getCursorPosition() const = 0;
};

struct ScopedMouseObserver : Mouse::Observer {
    ScopedMouseObserver() {
        Mouse::getInstance()->addObserver( this );
    }
    ~ScopedMouseObserver() {
        Mouse::getInstance()->removeObserver( this );
    }
    ScopedMouseObserver( const ScopedMouseObserver& ) = delete;
    ScopedMouseObserver( ScopedMouseObserver&& ) = delete;
    ScopedMouseObserver& operator = ( const ScopedMouseObserver& ) = delete;
    ScopedMouseObserver& operator = ( ScopedMouseObserver&& ) = delete;
};

}
