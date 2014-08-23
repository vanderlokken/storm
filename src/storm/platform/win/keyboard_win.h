#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/keyboard.h>
#include <storm/noncopyable.h>
#include <storm/observer_list.h>

#include <vector>

namespace storm {

class KeyboardWin : public Keyboard {
    NONCOPYABLE( KeyboardWin );
public:
    static KeyboardWin* getInstance();

    virtual ~KeyboardWin();

    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual bool isKeyPressed( Key ) const;

private:
    KeyboardWin();

    void processKeyboardInputEvent( const RAWKEYBOARD& );

    void processKeyPress( Key );
    void processKeyRepeat( Key );
    void processKeyRelease( Key );

    static const size_t KeyCount = 59;
    std::vector< bool > _keyPressed;

    ObserverList< Observer > _observers;

    WNDPROC _originalWindowProcedure;

    static LRESULT CALLBACK handleMessage( HWND, UINT, WPARAM, LPARAM );

    LRESULT handleInputMessage( WPARAM, LPARAM );
    LRESULT handleCharacterInputMessage( WPARAM, LPARAM );
    LRESULT handleActivationMessage( WPARAM, LPARAM );
};

}
