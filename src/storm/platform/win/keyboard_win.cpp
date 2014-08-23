#include <storm/platform/win/keyboard_win.h>

#include <map>
#include <memory>

#include <storm/platform/win/input_win.h>
#include <storm/platform/win/rendering_window_win.h>
#include <storm/platform/win/window_procedure_win.h>

// The following definitions were taken from MSDN
// See http://msdn.microsoft.com/en-us/library/ff543477%28v=VS.85%29.aspx

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_KEYBOARD
#define HID_USAGE_GENERIC_KEYBOARD ((USHORT) 0x06)
#endif

namespace storm {

KeyboardWin::KeyboardWin()
    : _keyPressed( KeyCount, false ),
      _originalWindowProcedure( nullptr )
{
    registerInputDevice( HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD );

    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    _originalWindowProcedure = replaceWindowProcedure( windowHandle, &KeyboardWin::handleMessage );
    return;
}

KeyboardWin::~KeyboardWin() {
    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    replaceWindowProcedure( windowHandle, _originalWindowProcedure );
    return;
}

void KeyboardWin::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void KeyboardWin::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

bool KeyboardWin::isKeyPressed( Key key ) const {
    const size_t keyIndex = static_cast<size_t>( key );
    if( keyIndex < KeyCount )
        return _keyPressed[keyIndex];
    else
        return false;
}

void KeyboardWin::processKeyboardInputEvent( const RAWKEYBOARD &keyboard ) {
    static const std::map< USHORT, Key > codes = {
        { VK_ESCAPE,   Key::Escape },
        { VK_F1,       Key::F1 },
        { VK_F2,       Key::F2 },
        { VK_F3,       Key::F3 },
        { VK_F4,       Key::F4 },
        { VK_F5,       Key::F5 },
        { VK_F6,       Key::F6 },
        { VK_F7,       Key::F7 },
        { VK_F8,       Key::F8 },
        { VK_F9,       Key::F9 },
        { VK_F10,      Key::F10 },
        { VK_F11,      Key::F11 },
        { VK_F12,      Key::F12 },
        { VK_NUMPAD0,  Key::Digit0 },
        { VK_NUMPAD1,  Key::Digit1 },
        { VK_NUMPAD2,  Key::Digit2 },
        { VK_NUMPAD3,  Key::Digit3 },
        { VK_NUMPAD4,  Key::Digit4 },
        { VK_NUMPAD5,  Key::Digit5 },
        { VK_NUMPAD6,  Key::Digit6 },
        { VK_NUMPAD7,  Key::Digit7 },
        { VK_NUMPAD8,  Key::Digit8 },
        { VK_NUMPAD9,  Key::Digit9 },
        { 'A',         Key::A },
        { 'B',         Key::B },
        { 'C',         Key::C },
        { 'D',         Key::D },
        { 'E',         Key::E },
        { 'F',         Key::F },
        { 'G',         Key::G },
        { 'H',         Key::H },
        { 'I',         Key::I },
        { 'J',         Key::J },
        { 'K',         Key::K },
        { 'L',         Key::L },
        { 'M',         Key::M },
        { 'N',         Key::N },
        { 'O',         Key::O },
        { 'P',         Key::P },
        { 'Q',         Key::Q },
        { 'R',         Key::R },
        { 'S',         Key::S },
        { 'T',         Key::T },
        { 'U',         Key::U },
        { 'V',         Key::V },
        { 'W',         Key::W },
        { 'X',         Key::X },
        { 'Y',         Key::Y },
        { 'Z',         Key::Z },
        { VK_LSHIFT,   Key::LeftShift },
        { VK_RSHIFT,   Key::RightShift },
        { VK_LCONTROL, Key::LeftControl },
        { VK_RCONTROL, Key::RightControl },
        { VK_SPACE,    Key::Space },
        { VK_LEFT,     Key::Left },
        { VK_RIGHT,    Key::Right },
        { VK_UP,       Key::Up },
        { VK_DOWN,     Key::Down },
        { VK_DELETE,   Key::Delete }
    };

    const bool isLeft = (keyboard.Flags & RI_KEY_E0) != 0;

    USHORT code = keyboard.VKey;
    if( code == VK_SHIFT )
        code = isLeft ? VK_LSHIFT : VK_RSHIFT;
    else if( code == VK_CONTROL )
        code = isLeft ? VK_LCONTROL : VK_RCONTROL;

    auto iterator = codes.find( code );

    if( iterator == codes.end() )
        return; // Ignore unknown keys

    const Key key = iterator->second;
    const size_t keyIndex = static_cast<size_t>( key );

    if( keyboard.Message == WM_KEYDOWN && _keyPressed[keyIndex] == false )
        processKeyPress( key );

    if( keyboard.Message == WM_KEYDOWN && _keyPressed[keyIndex] == true )
        processKeyRepeat( key );

    if( keyboard.Message == WM_KEYUP )
        processKeyRelease( key );

    return;
}

void KeyboardWin::processKeyPress( Key key ) {
    const size_t keyIndex = static_cast<size_t>( key );
    _keyPressed[keyIndex] = true;

    _observers.forEach([=]( const Observer &observer) {
        if( observer.onKeyPress )
            observer.onKeyPress( key );
    });
}

void KeyboardWin::processKeyRepeat( Key key ) {
    _observers.forEach([=]( const Observer &observer) {
        if( observer.onKeyRepeat )
            observer.onKeyRepeat( key );
    });
}

void KeyboardWin::processKeyRelease( Key key ) {

    // There might be some situations when key release events shouldn't be received

    // For example a user can press some key while the rendering window is not
    // active and then activate the rendering window and release the pressed key

    const size_t keyIndex = static_cast<size_t>( key );

    if( !_keyPressed[keyIndex] )
        return;

    _keyPressed[keyIndex] = false;

    _observers.forEach([=]( const Observer &observer) {
        if( observer.onKeyRelease )
            observer.onKeyRelease( key );
    });
}

const LRESULT USE_DEFAULT_PROCESSING = ~0U;

LRESULT CALLBACK KeyboardWin::handleMessage(
    HWND windowHandle, UINT message, WPARAM firstParameter, LPARAM secondParameter )
{
    auto keyboard = KeyboardWin::getInstance();

    LRESULT result = USE_DEFAULT_PROCESSING;

    switch( message ) {
    case WM_INPUT:
        result = keyboard->handleInputMessage( firstParameter, secondParameter );
        break;

    case WM_CHAR:
        result = keyboard->handleCharacterInputMessage( firstParameter, secondParameter );
        break;

    case WM_KEYDOWN:
        // By default VK_DELETE doesn't produce appropriate WM_CHAR message so
        // it's necessary to do this. 127 is an ASCII code of "delete" character
        if( firstParameter == VK_DELETE )
            ::SendMessage( windowHandle, WM_CHAR, 127, secondParameter );
        break;

    case WM_ACTIVATEAPP:
        result = keyboard->handleActivationMessage( firstParameter, secondParameter );
        break;
    }

    if( result != USE_DEFAULT_PROCESSING )
        return result;

    return ::CallWindowProc( keyboard->_originalWindowProcedure,
        windowHandle, message, firstParameter, secondParameter );
}

LRESULT KeyboardWin::handleInputMessage( WPARAM, LPARAM secondParameter ) {

    const HRAWINPUT inputHandle = reinterpret_cast< HRAWINPUT >( secondParameter );
    const RAWINPUT inputData = receiveInputData( inputHandle );

    if( inputData.header.dwType == RIM_TYPEKEYBOARD )
        processKeyboardInputEvent( inputData.data.keyboard );

    return USE_DEFAULT_PROCESSING;
}

LRESULT KeyboardWin::handleCharacterInputMessage( WPARAM firstParameter, LPARAM ) {
    _observers.forEach([=]( const Observer &observer) {
        if( observer.onCharacterInput )
            observer.onCharacterInput( firstParameter );
    });

    return USE_DEFAULT_PROCESSING;
}

LRESULT KeyboardWin::handleActivationMessage( WPARAM firstParameter, LPARAM ) {

    const BOOL activated = firstParameter;

    if( !activated )
        for( size_t keyIndex = 0; keyIndex < KeyCount; ++keyIndex )
            if( _keyPressed[keyIndex] ) processKeyRelease( static_cast<Key>(keyIndex) );

    return USE_DEFAULT_PROCESSING;
}

KeyboardWin* KeyboardWin::getInstance() {
    static const std::unique_ptr<KeyboardWin> instance( new KeyboardWin );
    return instance.get();
}

Keyboard* Keyboard::getInstance() {
    return KeyboardWin::getInstance();
}

}