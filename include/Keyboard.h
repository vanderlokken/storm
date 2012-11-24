#ifndef storm_Keyboard_h
#define storm_Keyboard_h

#include <memory>

#include "EventHandler.h"
#include "Noexcept.h"

namespace storm {

class Keyboard {
public:
    enum Key {
        KeyEscape,
        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,
        KeyDigit0,
        KeyDigit1,
        KeyDigit2,
        KeyDigit3,
        KeyDigit4,
        KeyDigit5,
        KeyDigit6,
        KeyDigit7,
        KeyDigit8,
        KeyDigit9,
        KeyA,
        KeyB,
        KeyC,
        KeyD,
        KeyE,
        KeyF,
        KeyG,
        KeyH,
        KeyI,
        KeyJ,
        KeyK,
        KeyL,
        KeyM,
        KeyN,
        KeyO,
        KeyP,
        KeyQ,
        KeyR,
        KeyS,
        KeyT,
        KeyU,
        KeyV,
        KeyW,
        KeyX,
        KeyY,
        KeyZ
    };
    
    struct KeyEvent {
        Key key;
    };
    
    struct KeyPressEvent : public KeyEvent { };
    struct KeyRepeatEvent : public KeyEvent { };
    struct KeyReleaseEvent : public KeyEvent { };
    
    static std::shared_ptr<Keyboard> getInstance();
    
    virtual ~Keyboard() noexcept { }
    
    virtual void addEventHandler( const EventHandler<KeyPressEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<KeyRepeatEvent>& ) = 0;
    virtual void addEventHandler( const EventHandler<KeyReleaseEvent>& ) = 0;
    
    virtual bool isKeyPressed( Key ) const noexcept = 0;
};

}

#endif