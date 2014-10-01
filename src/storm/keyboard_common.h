#pragma once

#include <vector>

#include <storm/keyboard.h>
#include <storm/noncopyable.h>
#include <storm/observer_list.h>

namespace storm {

class KeyboardCommon : public Keyboard {
    NONCOPYABLE( KeyboardCommon );
public:
    virtual void addObserver( const Observer* );
    virtual void removeObserver( const Observer* );

    virtual bool isKeyPressed( Key ) const;

protected:
    KeyboardCommon();

    void onKeyPress( Key );
    void onKeyRelease( Key );
    void onCharacterInput( CharacterCode );

    void onInputFocusLost();

private:
    enum class KeyState {
        Released,
        Pressed
    };

    std::vector<KeyState> _keyStates;
    ObserverList<Observer> _observers;
};

}
