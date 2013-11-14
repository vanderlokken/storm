#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/event_handler_vector.h>
#include <storm/mouse.h>
#include <storm/noncopyable.h>

namespace storm {

class MouseWin : public Mouse {
    NONCOPYABLE( MouseWin );
public:
    static MouseWin* getInstance();

    virtual ~MouseWin();

    virtual void addEventHandler( const EventHandler<ButtonPressEvent>& );
    virtual void addEventHandler( const EventHandler<ButtonReleaseEvent>& );
    virtual void addEventHandler( const EventHandler<WheelRotationEvent>& );
    virtual void addEventHandler( const EventHandler<MovementEvent>& );

    virtual bool isButtonPressed( Button ) const noexcept;

    virtual bool getCursorVisibility() const noexcept;
    virtual void setCursorVisibility( bool ) noexcept;

    virtual bool getCursorMovementRestriction() const noexcept;
    virtual void setCursorMovementRestriction( bool ) noexcept;

private:
    MouseWin();

    void processMouseInputEvent( const RAWMOUSE& );

    void processButtonPress( Button );
    void processButtonRelease( Button );
    void processWheelRotation( short distance );
    void processMovement( int x, int y );

    bool isCursorLockRequired() noexcept;
    bool isCursorInClientRectangle() noexcept;

    void lockCursor() noexcept;
    void unlockCursor() noexcept;

    static const size_t ButtonCount = 5;
    std::vector< bool > _buttonPressed;

    bool _cursorVisible;
    bool _cursorMovementRestricted;
    bool _cursorLocked;

    EventHandlerVector< ButtonPressEvent > _buttonPressEventHandlers;
    EventHandlerVector< ButtonReleaseEvent > _buttonReleaseEventHandlers;
    EventHandlerVector< WheelRotationEvent > _wheelRotationEventHandlers;
    EventHandlerVector< MovementEvent > _movementEventHandlers;

    WNDPROC _originalWindowProcedure;

    static LRESULT CALLBACK handleMessage( HWND, UINT, WPARAM, LPARAM );

    LRESULT handleInputMessage( WPARAM, LPARAM );
    LRESULT handleCursorMessage( WPARAM, LPARAM ) noexcept;
    LRESULT handleActivationMessage( WPARAM, LPARAM ) noexcept;
    LRESULT handleLeftButtonPressMessage( WPARAM, LPARAM ) noexcept;
};

}
