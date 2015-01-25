#pragma once

#include <storm/mouse.h>
#include <storm/observer_list.h>
#include <storm/platform/x11/input_x11.h>

namespace storm {

class MouseX11 : public Mouse {
public:
    MouseX11();

    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual bool isButtonPressed( Button ) const;

    virtual bool getCursorVisibility() const;
    virtual void setCursorVisibility( bool );

    virtual bool getCursorMovementRestriction() const;
    virtual void setCursorMovementRestriction( bool );

    virtual CursorPosition getCursorPosition() const;

private:
    void onButtonEvent( const XIDeviceEvent &event );

    CursorPosition _cursorPosition;

    ObserverList<Observer> _observers;

    InputX11::MouseEventListener _eventListener;
};

}
