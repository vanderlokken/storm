#include <storm/platform/x11/keyboard_x11.h>

#include <locale>
#include <map>
#include <memory>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

CharacterConversionDescriptor::CharacterConversionDescriptor(
    const char *fromEncoding, const char *toEncoding )
{
    _descriptor = iconv_open( toEncoding, fromEncoding );
    if( _descriptor == reinterpret_cast<iconv_t>(-1) )
        throwRuntimeError( "iconv_open has failed" );
}

CharacterConversionDescriptor::~CharacterConversionDescriptor() {
    iconv_close( _descriptor );
}

InputMethodHandleX11::InputMethodHandleX11( Display *display ) {
    _handle = ::XOpenIM(
        display,
        /* resourceDatabase = */ 0,
        /* resourceName = */ nullptr,
        /* resourceClass = */ nullptr );
    if( !_handle )
        throwRuntimeError( "::XOpenIM has failed" );
}

InputMethodHandleX11::~InputMethodHandleX11() {
    ::XCloseIM( _handle );
}

InputContextHandleX11::InputContextHandleX11(
    XIM inputMethod, XIMStyle inputStyle, Window window )
{
    _handle = ::XCreateIC( inputMethod,
        XNInputStyle, inputStyle, XNClientWindow, window, nullptr );
    if( !_handle )
        throwRuntimeError( "::XCreateIC has failed" );
}

InputContextHandleX11::~InputContextHandleX11() {
    ::XDestroyIC( _handle );
}

KeyboardX11::KeyboardX11( RenderingWindowX11 *renderingWindow ) :
    _utf32ConversionDescriptor( "UTF-8", "UTF-32" ),
    _inputMethodHandle( getDisplayHandleX11() ),
    _inputContextHandle( _inputMethodHandle,
        XIMPreeditNothing | XIMStatusNothing, renderingWindow->getHandle() )
{
    setlocale( LC_ALL, "en_US.UTF-8" );
    ::XSetLocaleModifiers( "" );

    unsigned long inputContextEventMask = 0;
    ::XGetICValues(
        _inputContextHandle, XNFilterEvents, &inputContextEventMask, nullptr );

    renderingWindow->addEventMask( inputContextEventMask |
        KeyPressMask | KeyReleaseMask | FocusChangeMask );

    if( renderingWindow->isActive() )
        ::XSetICFocus( _inputContextHandle );

    // Note: in X11 there's no specific event for a key repetition. Alternating
    // 'KeyPress' and 'KeyRelease' events are used instead.

    _eventListener.onEvent[KeyPress] = [=]( const XEvent &event ) {
        onKeyEvent( event );

        std::vector<char> buffer( 16 );
        while( true ) {
            // For some reason 'Xutf8LookupString' requires non-const pointer to
            // an 'XKeyPressedEvent' value. Thus we need to make a temporary
            // copy.
            XKeyPressedEvent keyEvent = event.xkey;
            Status status;

            const int result = ::Xutf8LookupString( _inputContextHandle,
                &keyEvent, buffer.data(), buffer.size(), nullptr, &status );

            if( status == XBufferOverflow && static_cast<unsigned int>(result) >
                buffer.size() )
            {
                buffer.resize( result );
            } else if( status == XLookupNone ) {
                return;
            } else {
                break;
            }
        }

        std::vector<CharacterCode> characters( buffer.size() );

        char *sourceData = buffer.data();
        char *convertedData = reinterpret_cast<char*>( characters.data() );
        size_t sourceSize = buffer.size();
        size_t convertedSize = characters.size() * sizeof( CharacterCode );

        iconv( _utf32ConversionDescriptor,
            &sourceData,
            &sourceSize,
            &convertedData,
            &convertedSize );

        for( CharacterCode characterCode : characters )
            if( characterCode )
                onCharacterInput( characterCode );
            else
                break;
    };

    _eventListener.onEvent[KeyRelease] = [=]( const XEvent &event ) {
        Display *display = getDisplayHandleX11();

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

    _eventListener.onEvent[FocusIn] = [=]( const XEvent& ) {
        ::XSetICFocus( _inputContextHandle );
    };

    _eventListener.onEvent[FocusOut] = [=]( const XEvent& ) {
        ::XUnsetICFocus( _inputContextHandle );
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
    static const std::unique_ptr<KeyboardX11> instance(
        new KeyboardX11(RenderingWindowX11::getInstance()) );
    return instance.get();
}

}
