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

KeyboardWin::KeyboardWin() : _originalWindowProcedure( nullptr ) {
    registerInputDevice( HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_KEYBOARD );

    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    _originalWindowProcedure = replaceWindowProcedure(
        windowHandle, &KeyboardWin::handleMessage );
}

KeyboardWin::~KeyboardWin() {
    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    replaceWindowProcedure( windowHandle, _originalWindowProcedure );
}

void KeyboardWin::onEvent( const RAWKEYBOARD &keyboard ) {
    typedef std::pair<int, bool> KeyCode;

    // The following integer constants and respective Key values are taken from
    // http://msdn.microsoft.com/en-us/library/ms894073.aspx
    static const std::map<KeyCode, Key> keyCodes = {
        // Functional keys
        {{1, false}, Key::Escape},
        {{59, false}, Key::F1},
        {{60, false}, Key::F2},
        {{61, false}, Key::F3},
        {{62, false}, Key::F4},
        {{63, false}, Key::F5},
        {{64, false}, Key::F6},
        {{65, false}, Key::F7},
        {{66, false}, Key::F8},
        {{67, false}, Key::F9},
        {{68, false}, Key::F10},
        {{87, false}, Key::F11},
        {{88, false}, Key::F12},
        // Digits
        {{11, false}, Key::Digit0},
        {{2, false}, Key::Digit1},
        {{3, false}, Key::Digit2},
        {{4, false}, Key::Digit3},
        {{5, false}, Key::Digit4},
        {{6, false}, Key::Digit5},
        {{7, false}, Key::Digit6},
        {{8, false}, Key::Digit7},
        {{9, false}, Key::Digit8},
        {{10, false}, Key::Digit9},
        // Letters
        {{30, false}, Key::A},
        {{48, false}, Key::B},
        {{46, false}, Key::C},
        {{32, false}, Key::D},
        {{18, false}, Key::E},
        {{33, false}, Key::F},
        {{34, false}, Key::G},
        {{35, false}, Key::H},
        {{23, false}, Key::I},
        {{36, false}, Key::J},
        {{37, false}, Key::K},
        {{38, false}, Key::L},
        {{50, false}, Key::M},
        {{49, false}, Key::N},
        {{24, false}, Key::O},
        {{25, false}, Key::P},
        {{16, false}, Key::Q},
        {{19, false}, Key::R},
        {{31, false}, Key::S},
        {{20, false}, Key::T},
        {{22, false}, Key::U},
        {{47, false}, Key::V},
        {{17, false}, Key::W},
        {{45, false}, Key::X},
        {{21, false}, Key::Y},
        {{44, false}, Key::Z},
        // Symbols
        {{41, false}, Key::Tilde},
        {{12, false}, Key::Minus},
        {{13, false}, Key::Plus},
        {{26, false}, Key::LeftBracket},
        {{27, false}, Key::RightBracket},
        {{39, false}, Key::Colon},
        {{51, false}, Key::Comma},
        {{52, false}, Key::Period},
        {{53, false}, Key::Slash},
        {{43, false}, Key::Backslash},
        {{40, false}, Key::Apostrophe},
        // Editing keys
        {{28, false}, Key::Enter},
        {{57, false}, Key::Space},
        {{15, false}, Key::Tab},
        {{14, false}, Key::Backspace},
        {{83, true}, Key::Delete},
        {{82, true}, Key::Insert},
        // Navigation keys
        {{75, true}, Key::Left},
        {{77, true}, Key::Right},
        {{72, true}, Key::Up},
        {{80, true}, Key::Down},
        {{71, true}, Key::Home},
        {{79, true}, Key::End},
        {{73, true}, Key::PageUp},
        {{81, true}, Key::PageDown},
        // Modifier keys
        {{42, false}, Key::LeftShift},
        {{54, false}, Key::RightShift},
        {{29, false}, Key::LeftControl},
        {{29, true}, Key::RightControl},
        {{56, false}, Key::LeftAlter},
        {{56, true}, Key::RightAlter},
        // Keypad keys
        {{69, false}, Key::NumLock},
        {{82, false}, Key::Keypad0},
        {{79, false}, Key::Keypad1},
        {{80, false}, Key::Keypad2},
        {{81, false}, Key::Keypad3},
        {{75, false}, Key::Keypad4},
        {{76, false}, Key::Keypad5},
        {{77, false}, Key::Keypad6},
        {{71, false}, Key::Keypad7},
        {{72, false}, Key::Keypad8},
        {{73, false}, Key::Keypad9},
        {{53, true}, Key::KeypadSlash},
        {{55, false}, Key::KeypadAsterisk},
        {{74, false}, Key::KeypadMinus},
        {{78, false}, Key::KeypadPlus},
        {{28, true}, Key::KeypadEnter},
        {{83, false}, Key::KeypadDelete},
        // Utility keys
        {{58, false}, Key::CapsLock},
        {{70, false}, Key::ScrollLock},
        {{55, true}, Key::PrintScreen},
        {{84, false}, Key::PrintScreen}, // When Alt is pressed
        // TODO: detect Key::Pause
        {{91, true}, Key::LeftCommand},
        {{92, true}, Key::RightCommand},
        {{93, true}, Key::Menu}
    };

    const bool isReleased = (keyboard.Flags & RI_KEY_BREAK) != 0;
    const bool isExtended = (keyboard.Flags & RI_KEY_E0) != 0;

    const auto iterator = keyCodes.find( {keyboard.MakeCode, isExtended} );
    if( iterator != keyCodes.end() ) {
        if( !isReleased )
            onKeyPress( iterator->second );
        else
            onKeyRelease( iterator->second );
    }
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
        onEvent( inputData.data.keyboard );

    return USE_DEFAULT_PROCESSING;
}

LRESULT KeyboardWin::handleCharacterInputMessage( WPARAM firstParameter, LPARAM ) {
    onCharacterInput( firstParameter );
    return USE_DEFAULT_PROCESSING;
}

LRESULT KeyboardWin::handleActivationMessage( WPARAM firstParameter, LPARAM ) {
    const BOOL activated = firstParameter;

    if( !activated )
        onInputFocusLost();

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
