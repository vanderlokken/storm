#include <storm/platform/win/keyboard_win.h>

#include <algorithm>
#include <array>

#include <storm/platform/win/input_win.h>
#include <storm/platform/win/rendering_window_win.h>
#include <storm/platform/win/window_procedure_win.h>
#include <storm/throw_exception.h>

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

void KeyboardWin::addEventHandler( const EventHandler<KeyPressEvent> &handler ) {
    _keyPressEventHandlers.addEventHandler( handler );
    return;
}

void KeyboardWin::addEventHandler( const EventHandler<KeyRepeatEvent> &handler ) {
    _keyRepeatEventHandlers.addEventHandler( handler );
    return;
}

void KeyboardWin::addEventHandler( const EventHandler<KeyReleaseEvent> &handler ) {
    _keyReleaseEventHandlers.addEventHandler( handler );
    return;
}

bool KeyboardWin::isKeyPressed( Key key ) const {
    const size_t keyIndex = static_cast<size_t>( key );
    if( keyIndex < KeyCount )
        return _keyPressed[keyIndex];
    else
        return false;
}

void KeyboardWin::processKeyboardInputEvent( const RAWKEYBOARD &keyboard ) {
    Key key;

    try {
        key = convertKey( keyboard.VKey );

    } catch( storm::Exception& ) {
        // Unknown keys are silently ignored
        return;
    }

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

    KeyPressEvent event; event.key = key;
    _keyPressEventHandlers( event );
    return;
}

void KeyboardWin::processKeyRepeat( Key key ) {
    KeyRepeatEvent event; event.key = key;
    _keyRepeatEventHandlers( event );
    return;
}

void KeyboardWin::processKeyRelease( Key key ) {

    // There might be some situations when key release events shouldn't be received

    // For example a user can press some key while the rendering window is not
    // active and then activate the rendering window and release the pressed key

    const size_t keyIndex = static_cast<size_t>( key );

    if( !_keyPressed[keyIndex] )
        return;

    _keyPressed[keyIndex] = false;

    KeyReleaseEvent event; event.key = key;
    _keyReleaseEventHandlers( event );
    return;
}

Keyboard::Key KeyboardWin::convertKey( USHORT code ) {
    std::array< USHORT, KeyCount > codes = {
        VK_ESCAPE,  // Escape
        VK_F1,      // F1
        VK_F2,      // F2
        VK_F3,      // F3
        VK_F4,      // F4
        VK_F5,      // F5
        VK_F6,      // F6
        VK_F7,      // F7
        VK_F8,      // F8
        VK_F9,      // F9
        VK_F10,     // F10
        VK_F11,     // F11
        VK_F12,     // F12
        VK_NUMPAD0, // Digit0
        VK_NUMPAD1, // Digit1
        VK_NUMPAD2, // Digit2
        VK_NUMPAD3, // Digit3
        VK_NUMPAD4, // Digit4
        VK_NUMPAD5, // Digit5
        VK_NUMPAD6, // Digit6
        VK_NUMPAD7, // Digit7
        VK_NUMPAD8, // Digit8
        VK_NUMPAD9, // Digit9
        'A',        // A
        'B',        // B
        'C',        // C
        'D',        // D
        'E',        // E
        'F',        // F
        'G',        // G
        'H',        // H
        'I',        // I
        'J',        // J
        'K',        // K
        'L',        // L
        'M',        // M
        'N',        // N
        'O',        // O
        'P',        // P
        'Q',        // Q
        'R',        // R
        'S',        // S
        'T',        // T
        'U',        // U
        'V',        // V
        'W',        // W
        'X',        // X
        'Y',        // Y
        'Z',        // Z
        VK_SPACE    // Space
    };

    auto searchResult = std::find( codes.cbegin(), codes.cend(), code );

    if( searchResult == codes.cend() )
        throwRuntimeError( "'code' is invalid" );

    return static_cast< Keyboard::Key >( searchResult - codes.cbegin() );
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