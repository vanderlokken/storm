#include <storm/keyboard_common.h>

namespace storm {

const size_t maximalKeysNumber = 255;

KeyboardCommon::KeyboardCommon() :
    _keyStates( maximalKeysNumber, KeyState::Released )
{
}

void KeyboardCommon::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void KeyboardCommon::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

bool KeyboardCommon::isKeyPressed( Key key ) const {
    const size_t keyIndex = static_cast<size_t>( key );
    return _keyStates[keyIndex] == KeyState::Pressed;
}

void KeyboardCommon::onKeyPress( Key key ) {
    const size_t keyIndex = static_cast<size_t>( key );

    if( _keyStates[keyIndex] == KeyState::Released ) {
        _keyStates[keyIndex] = KeyState::Pressed;

        _observers.notify( &Observer::onKeyPress, key );
    } else {
        _observers.notify( &Observer::onKeyRepeat, key );
    }
}

void KeyboardCommon::onKeyRelease( Key key ) {
    // There might be some situations when key release events shouldn't be
    // detected. For example a user can press some key while the rendering
    // window is not active and then activate the rendering window and release
    // the pressed key.

    const size_t keyIndex = static_cast<size_t>( key );

    if( _keyStates[keyIndex] == KeyState::Pressed ) {
        _keyStates[keyIndex] = KeyState::Released;

        _observers.notify( &Observer::onKeyRelease, key );
    }
}

void KeyboardCommon::onCharacterInput( CharacterCode code ) {
    _observers.notify( &Observer::onCharacterInput, code );
}

void KeyboardCommon::onInputFocusLost() {
    for( size_t keyIndex = 0; keyIndex < _keyStates.size(); ++keyIndex )
        if( _keyStates[keyIndex] == KeyState::Pressed )
            onKeyRelease( static_cast<Key>(keyIndex) );
}

}
