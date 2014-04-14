#pragma once

#include <cstdint>

#include <storm/event_handler.h>

namespace storm {

class Keyboard {
public:
    enum class Key {
        Escape,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Digit0,
        Digit1,
        Digit2,
        Digit3,
        Digit4,
        Digit5,
        Digit6,
        Digit7,
        Digit8,
        Digit9,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LeftShift, RightShift,
        LeftControl, RightControl,
        Space,
        Left, Right, Up, Down,
        Delete
    };

    struct KeyEvent {
        Key key;
    };

    struct KeyPressEvent : public KeyEvent { };
    struct KeyRepeatEvent : public KeyEvent { };
    struct KeyReleaseEvent : public KeyEvent { };

    struct CharacterInputEvent {
        uint32_t code;
    };

    static Keyboard* getInstance();

    virtual ~Keyboard() { }

    virtual void addEventHandler( const EventHandler<KeyPressEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<KeyRepeatEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<KeyReleaseEvent>& ) = 0;

    virtual void addEventHandler( const EventHandler<CharacterInputEvent>& ) = 0;

    virtual bool isKeyPressed( Key ) const = 0;
};

}
