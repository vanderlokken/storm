#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/event_handler_vector.h>
#include <storm/keyboard.h>
#include <storm/noncopyable.h>

namespace storm {

class KeyboardWin : public Keyboard {
    NONCOPYABLE( KeyboardWin );
public:
    static KeyboardWin* getInstance();

    virtual ~KeyboardWin();

    virtual void addEventHandler( const EventHandler<KeyPressEvent>& );
    virtual void addEventHandler( const EventHandler<KeyRepeatEvent>& );
    virtual void addEventHandler( const EventHandler<KeyReleaseEvent>& );

    virtual void addEventHandler( const EventHandler<CharacterInputEvent>& );

    virtual bool isKeyPressed( Key ) const;

private:
    KeyboardWin();

    void processKeyboardInputEvent( const RAWKEYBOARD& );

    void processKeyPress( Key );
    void processKeyRepeat( Key );
    void processKeyRelease( Key );

    static Key convertKey( USHORT code );

    static const size_t KeyCount = 54;
    std::vector< bool > _keyPressed;

    EventHandlerVector< KeyPressEvent > _keyPressEventHandlers;
    EventHandlerVector< KeyRepeatEvent > _keyRepeatEventHandlers;
    EventHandlerVector< KeyReleaseEvent > _keyReleaseEventHandlers;

    EventHandlerVector< CharacterInputEvent > _characterInputEventHandlers;

    WNDPROC _originalWindowProcedure;

    static LRESULT CALLBACK handleMessage( HWND, UINT, WPARAM, LPARAM );

    LRESULT handleInputMessage( WPARAM, LPARAM );
    LRESULT handleCharacterInputMessage( WPARAM, LPARAM );
    LRESULT handleActivationMessage( WPARAM, LPARAM );
};

}
