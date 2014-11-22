#pragma once

#include <storm/mouse.h>
#include <storm/noncopyable.h>
#include <storm/observer_list.h>
#include <storm/platform/win/api_win.h>

#include <vector>

namespace storm {

class MouseWin : public Mouse {
    NONCOPYABLE( MouseWin );
public:
    static MouseWin* getInstance();

    virtual ~MouseWin();

    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual bool isButtonPressed( Button ) const;

    virtual bool getCursorVisibility() const;
    virtual void setCursorVisibility( bool );

    virtual bool getCursorMovementRestriction() const;
    virtual void setCursorMovementRestriction( bool );

    virtual CursorPosition getCursorPosition() const;

private:
    MouseWin();

    void processMouseInputEvent( const RAWMOUSE& );

    void processButtonPress( Button );
    void processButtonRelease( Button );
    void processWheelRotation( short distance );
    void processMovement( Movement );
    void processCursorMovement( CursorPosition );

    bool isCursorLockRequired();
    bool isCursorInClientRectangle();

    void lockCursor();
    void unlockCursor();

    static const size_t ButtonCount = 5;
    std::vector< bool > _buttonPressed;

    bool _cursorVisible;
    bool _cursorMovementRestricted;
    bool _cursorLocked;

    ObserverList< Observer > _observers;

    WNDPROC _originalWindowProcedure;

    static LRESULT CALLBACK handleMessage( HWND, UINT, WPARAM, LPARAM );

    LRESULT handleInputMessage( WPARAM, LPARAM );
    LRESULT handleCursorMessage( WPARAM, LPARAM );
    LRESULT handleActivationMessage( WPARAM, LPARAM );
    LRESULT handleLeftButtonPressMessage( WPARAM, LPARAM );
    LRESULT handleCursorMovementMessage( WPARAM, LPARAM );
    LRESULT handleSystemCommandMessage( WPARAM, LPARAM );
};

}
