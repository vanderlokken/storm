#include <storm/platform/x11/keyboard_x11.h>

#include <map>
#include <memory>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/platform/x11/rendering_window_x11.h>
#include <storm/throw_exception.h>

namespace storm {

KeyboardX11::KeyboardX11( Display *display, Window window ) {
    XWindowAttributes windowAttributes = {};

    if( !::XGetWindowAttributes(display, window, &windowAttributes) )
        throwRuntimeError( "::XGetWindowAttributes has failed" );

    windowAttributes.your_event_mask |=
        KeyPressMask | KeyReleaseMask | FocusChangeMask;

    if( !::XSelectInput(display, window, windowAttributes.your_event_mask) )
        throwRuntimeError( "::XSelectInput has failed" );

    // Note: in X11 there's no specific event for a key repetition. Alternating
    // 'KeyPress' and 'KeyRelease' events are used instead.

    _eventListener.onEvent[KeyPress] = [=]( const XEvent &event ) {
        onKeyEvent( event );
        // TODO: character input
    };

    _eventListener.onEvent[KeyRelease] = [=]( const XEvent &event ) {
        // Ignore fake KeyRelease events generated during key repetition.
        ::XSync( display, /*discardQueuedEvents = */ false );
        if( ::XEventsQueued(display, QueuedAlready) ) {
            XEvent nextEvent;
            ::XPeekEvent( display, &nextEvent );
            if( nextEvent.type == KeyPress &&
                nextEvent.xkey.time == event.xkey.time &&
                nextEvent.xkey.keycode == event.xkey.keycode )
            {
                return;
            }
        }

        onKeyEvent( event );
    };

    _eventListener.onEvent[FocusOut] = [=]( const XEvent& ) {
        onInputFocusLost();
    };
}

void KeyboardX11::onKeyEvent( const XEvent &event ) {
    // The following integer constants and respective Key values are taken from
    // the default 'xmodmap -pke' command output.
    static const std::map<unsigned int, Key> keyCodes = {
        // Functional keys
        {9,  Key::Escape},
        {67, Key::F1},
        {68, Key::F2},
        {69, Key::F3},
        {70, Key::F4},
        {71, Key::F5},
        {72, Key::F6},
        {73, Key::F7},
        {74, Key::F8},
        {75, Key::F9},
        {76, Key::F10},
        {95, Key::F11},
        {96, Key::F12},
        // Digits
        {10, Key::Digit1},
        {11, Key::Digit2},
        {12, Key::Digit3},
        {13, Key::Digit4},
        {14, Key::Digit5},
        {15, Key::Digit6},
        {16, Key::Digit7},
        {17, Key::Digit8},
        {18, Key::Digit9},
        {19, Key::Digit0},
        // Letters
        {24, Key::Q},
        {25, Key::W},
        {26, Key::E},
        {27, Key::R},
        {28, Key::T},
        {29, Key::Y},
        {30, Key::U},
        {31, Key::I},
        {32, Key::O},
        {33, Key::P},
        {38, Key::A},
        {39, Key::S},
        {40, Key::D},
        {41, Key::F},
        {42, Key::G},
        {43, Key::H},
        {44, Key::J},
        {45, Key::K},
        {46, Key::L},
        {52, Key::Z},
        {53, Key::X},
        {54, Key::C},
        {55, Key::V},
        {56, Key::B},
        {57, Key::N},
        {58, Key::M},
        // Symbols
        {49, Key::Tilde},
        {20, Key::Minus},
        {21, Key::Plus},
        {34, Key::LeftBracket},
        {35, Key::RightBracket},
        {47, Key::Colon},
        {59, Key::Comma},
        {60, Key::Period},
        {61, Key::Slash},
        {51, Key::Backslash},
        {48, Key::Apostrophe},
        // Editing keys
        {36, Key::Enter},
        {65, Key::Space},
        {23, Key::Tab},
        {22, Key::Backspace},
        {119, Key::Delete},
        {118, Key::Insert},
        // Navigation keys
        {113, Key::Left},
        {114, Key::Right},
        {111, Key::Up},
        {116, Key::Down},
        {110, Key::Home},
        {115, Key::End},
        {112, Key::PageUp},
        {117, Key::PageDown},
        // Modifier keys
        {50, Key::LeftShift},
        {62, Key::RightShift},
        {37, Key::LeftControl},
        {105, Key::RightControl},
        {64, Key::LeftAlter},
        {108, Key::RightAlter},
        // Keypad keys
        {77, Key::NumLock},
        {90, Key::Keypad0},
        {79, Key::Keypad1},
        {80, Key::Keypad2},
        {81, Key::Keypad3},
        {83, Key::Keypad4},
        {84, Key::Keypad5},
        {85, Key::Keypad6},
        {87, Key::Keypad7},
        {88, Key::Keypad8},
        {89, Key::Keypad9},
        {106, Key::KeypadSlash},
        {63, Key::KeypadAsterisk},
        {82, Key::KeypadMinus},
        {86, Key::KeypadPlus},
        {104, Key::KeypadEnter},
        {91, Key::KeypadDelete},
        // Utility keys
        {66, Key::CapsLock},
        {78, Key::ScrollLock},
        {107, Key::PrintScreen},
        {127, Key::Pause},
        {133, Key::LeftCommand},
        {134, Key::RightCommand},
        {135, Key::Menu}
    };

    const auto iterator = keyCodes.find( event.xkey.keycode );
    if( iterator != keyCodes.end() ) {
        if( event.type == KeyPress )
            onKeyPress( iterator->second );
        else if( event.type == KeyRelease )
            onKeyRelease( iterator->second );
    }
}

Keyboard* Keyboard::getInstance() {
    const auto create = [] {
        Window window = RenderingWindowX11::getInstance()->getHandle();
        return new KeyboardX11( getDisplayHandleX11(), window );
    };
    static const std::unique_ptr<KeyboardX11> instance( create() );
    return instance.get();
}

}
