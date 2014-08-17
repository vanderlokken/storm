#pragma once

#include <cstdint>
#include <functional>

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

    typedef uint32_t CharacterCode;

    struct Observer {
        std::function<void(Key)> onKeyPress;
        std::function<void(Key)> onKeyRelease;
        std::function<void(Key)> onKeyRepeat;
        std::function<void(CharacterCode)> onCharacterInput;
    };

    static Keyboard* getInstance();

    virtual ~Keyboard() {}

    virtual void addObserver( const Observer* ) = 0;
    virtual void removeObserver( const Observer* ) = 0;

    virtual bool isKeyPressed( Key ) const = 0;
};

struct ScopedKeyboardObserver : Keyboard::Observer {
    ScopedKeyboardObserver() {
        Keyboard::getInstance()->addObserver( this );
    }
    ~ScopedKeyboardObserver() {
        Keyboard::getInstance()->removeObserver( this );
    }
    ScopedKeyboardObserver( const ScopedKeyboardObserver& ) = delete;
    ScopedKeyboardObserver( const ScopedKeyboardObserver&& ) = delete;
    ScopedKeyboardObserver&
        operator = ( const ScopedKeyboardObserver& ) = delete;
    ScopedKeyboardObserver&
        operator = ( const ScopedKeyboardObserver&& ) = delete;
};

}
