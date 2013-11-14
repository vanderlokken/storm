#include <storm/platform/win/keyboard_win.h>

#include <algorithm>
#include <array>

#include <storm/exception.h>
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

bool KeyboardWin::isKeyPressed( Key key ) const noexcept {
    if( key < KeyCount )
        return _keyPressed[key];
    else
        return false;
}

void KeyboardWin::processKeyboardInputEvent( const RAWKEYBOARD &keyboard ) {
    Key key;

    try {
        key = convertKey( keyboard.VKey );

    } catch( std::invalid_argument& ) {
        // Unknown keys are silently ignored
        return;
    }

    if( keyboard.Message == WM_KEYDOWN && _keyPressed[key] == false )
        processKeyPress( key );

    if( keyboard.Message == WM_KEYDOWN && _keyPressed[key] == true )
        processKeyRepeat( key );

    if( keyboard.Message == WM_KEYUP )
        processKeyRelease( key );

    return;
}

void KeyboardWin::processKeyPress( Key key ) {
    _keyPressed[key] = true;

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

    if( !_keyPressed[key] )
        return;

    _keyPressed[key] = false;

    KeyReleaseEvent event; event.key = key;
    _keyReleaseEventHandlers( event );
    return;
}

Keyboard::Key KeyboardWin::convertKey( USHORT code ) {
    std::array< USHORT, KeyCount > codes = {
        VK_ESCAPE,  // KeyEscape
        VK_F1,      // KeyF1
        VK_F2,      // KeyF2
        VK_F3,      // KeyF3
        VK_F4,      // KeyF4
        VK_F5,      // KeyF5
        VK_F6,      // KeyF6
        VK_F7,      // KeyF7
        VK_F8,      // KeyF8
        VK_F9,      // KeyF9
        VK_F10,     // KeyF10
        VK_F11,     // KeyF11
        VK_F12,     // KeyF12
        VK_NUMPAD0, // KeyDigit0
        VK_NUMPAD1, // KeyDigit1
        VK_NUMPAD2, // KeyDigit2
        VK_NUMPAD3, // KeyDigit3
        VK_NUMPAD4, // KeyDigit4
        VK_NUMPAD5, // KeyDigit5
        VK_NUMPAD6, // KeyDigit6
        VK_NUMPAD7, // KeyDigit7
        VK_NUMPAD8, // KeyDigit8
        VK_NUMPAD9, // KeyDigit9
        'A',        // KeyA
        'B',        // KeyB
        'C',        // KeyC
        'D',        // KeyD
        'E',        // KeyE
        'F',        // KeyF
        'G',        // KeyG
        'H',        // KeyH
        'I',        // KeyI
        'J',        // KeyJ
        'K',        // KeyK
        'L',        // KeyL
        'M',        // KeyM
        'N',        // KeyN
        'O',        // KeyO
        'P',        // KeyP
        'Q',        // KeyQ
        'R',        // KeyR
        'S',        // KeyS
        'T',        // KeyT
        'U',        // KeyU
        'V',        // KeyV
        'W',        // KeyW
        'X',        // KeyX
        'Y',        // KeyY
        'Z',        // KeyZ
        VK_SPACE    // KeySpace
    };

    auto searchResult = std::find( codes.cbegin(), codes.cend(), code );

    if( searchResult == codes.cend() )
        throwInvalidArgument( "'code' is invalid" );

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

LRESULT KeyboardWin::handleActivationMessage( WPARAM firstParameter, LPARAM ) noexcept {

    const BOOL activated = firstParameter;

    if( !activated )
        for( size_t keyIndex = 0; keyIndex < KeyCount; ++keyIndex )
            if( _keyPressed[keyIndex] ) processKeyRelease( static_cast<Key>(keyIndex) );

    return USE_DEFAULT_PROCESSING;
}

std::shared_ptr<KeyboardWin> KeyboardWin::getInstance() {
    static const std::shared_ptr<KeyboardWin> instance( new KeyboardWin );
    return instance;
}

std::shared_ptr<Keyboard> Keyboard::getInstance() {
    return KeyboardWin::getInstance();
}

}