#include <storm/platform/x11/keyboard_state_xkb.h>

#include <xkbcommon/xkbcommon-keysyms.h>

namespace storm {

KeyboardStateXkb::KeyboardStateXkb( xcb_connection_t *connection ) :
    _connection( connection ),
    _context( xkb_context_new(XKB_CONTEXT_NO_FLAGS) )
{
    if( !_context ) {
        // TODO: handle errors
    }

    const int32_t deviceId =
        xkb_x11_get_core_keyboard_device_id( _connection );

    if( deviceId == -1 ) {
        // TODO: handle errors
    }

    _keymap = xkb_x11_keymap_new_from_device(
        _context, _connection, deviceId, XKB_KEYMAP_COMPILE_NO_FLAGS );

    if( !_keymap ) {
        // TODO: handle errors
    }

    _state = xkb_x11_state_new_from_device(
        _keymap, _connection, deviceId );

    if( !_state ) {
        // TODO: handle errors
    }

    selectEvents( deviceId );
    updateKeycodeMapping();
}

KeyboardStateXkb::~KeyboardStateXkb() {
    xkb_state_unref( _state );
    xkb_keymap_unref( _keymap );
    xkb_context_unref( _context );
}

std::optional<KeyboardKey> KeyboardStateXkb::getKey(
    xkb_keycode_t keycode ) const
{
    const auto iterator = _keycodeMapping.find( keycode );

    if( iterator != _keycodeMapping.end() ) {
        return iterator->second;
    }

    return std::nullopt;
}

std::optional<char32_t> KeyboardStateXkb::getCharacter(
    xkb_keycode_t keycode ) const
{
    if( const char32_t character =
            xkb_state_key_get_utf32(_state, keycode) ) {
        return character;
    }

    return std::nullopt;
}

void KeyboardStateXkb::update(
    const xcb_xkb_state_notify_event_t &event ) const
{
    xkb_state_update_mask(
        _state,
        event.baseMods,
        event.latchedMods,
        event.lockedMods,
        event.baseGroup,
        event.latchedGroup,
        event.lockedGroup );
}

void KeyboardStateXkb::selectEvents( int32_t deviceId ) {
    const auto requiredMapParts =
        XCB_XKB_MAP_PART_KEY_TYPES |
        XCB_XKB_MAP_PART_KEY_SYMS |
        XCB_XKB_MAP_PART_MODIFIER_MAP |
        XCB_XKB_MAP_PART_EXPLICIT_COMPONENTS |
        XCB_XKB_MAP_PART_KEY_ACTIONS |
        XCB_XKB_MAP_PART_VIRTUAL_MODS |
        XCB_XKB_MAP_PART_VIRTUAL_MOD_MAP;

    const auto requiredStateDetails =
        XCB_XKB_STATE_PART_MODIFIER_BASE |
        XCB_XKB_STATE_PART_MODIFIER_LATCH |
        XCB_XKB_STATE_PART_MODIFIER_LOCK |
        XCB_XKB_STATE_PART_GROUP_BASE |
        XCB_XKB_STATE_PART_GROUP_LATCH |
        XCB_XKB_STATE_PART_GROUP_LOCK;

    xcb_xkb_select_events_details_t selectEventDetails = {};
    selectEventDetails.affectNewKeyboard = XCB_XKB_NKN_DETAIL_KEYCODES;
    selectEventDetails.newKeyboardDetails = XCB_XKB_NKN_DETAIL_KEYCODES;
    selectEventDetails.affectState = requiredStateDetails;
    selectEventDetails.stateDetails = requiredStateDetails;

    xcb_xkb_select_events_aux(
        _connection,
        deviceId,
        XCB_XKB_EVENT_TYPE_NEW_KEYBOARD_NOTIFY |
        XCB_XKB_EVENT_TYPE_MAP_NOTIFY |
        XCB_XKB_EVENT_TYPE_STATE_NOTIFY,
        0,
        0,
        requiredMapParts,
        requiredMapParts,
        &selectEventDetails );
}

void KeyboardStateXkb::updateKeycodeMapping() {
    auto addMapping = [=]( const char *name, KeyboardKey key ) {
        const xkb_keycode_t keycode = xkb_keymap_key_by_name( _keymap, name );

        if( keycode != XKB_KEYCODE_INVALID ) {
            _keycodeMapping[keycode] = key;
        }
    };

    _keycodeMapping.clear();

    addMapping( "ESC",  KeyboardKey::Escape );
    addMapping( "FK01", KeyboardKey::F1 );
    addMapping( "FK02", KeyboardKey::F2 );
    addMapping( "FK03", KeyboardKey::F3 );
    addMapping( "FK04", KeyboardKey::F4 );
    addMapping( "FK05", KeyboardKey::F5 );
    addMapping( "FK06", KeyboardKey::F6 );
    addMapping( "FK07", KeyboardKey::F7 );
    addMapping( "FK08", KeyboardKey::F8 );
    addMapping( "FK09", KeyboardKey::F9 );
    addMapping( "FK10", KeyboardKey::F10 );
    addMapping( "FK11", KeyboardKey::F11 );
    addMapping( "FK12", KeyboardKey::F12 );
    addMapping( "AE10", KeyboardKey::Digit0 );
    addMapping( "AE01", KeyboardKey::Digit1 );
    addMapping( "AE02", KeyboardKey::Digit2 );
    addMapping( "AE03", KeyboardKey::Digit3 );
    addMapping( "AE04", KeyboardKey::Digit4 );
    addMapping( "AE05", KeyboardKey::Digit5 );
    addMapping( "AE06", KeyboardKey::Digit6 );
    addMapping( "AE07", KeyboardKey::Digit7 );
    addMapping( "AE08", KeyboardKey::Digit8 );
    addMapping( "AE09", KeyboardKey::Digit9 );
    addMapping( "AC01", KeyboardKey::A );
    addMapping( "AB05", KeyboardKey::B );
    addMapping( "AB03", KeyboardKey::C );
    addMapping( "AC03", KeyboardKey::D );
    addMapping( "AD03", KeyboardKey::E );
    addMapping( "AC04", KeyboardKey::F );
    addMapping( "AC05", KeyboardKey::G );
    addMapping( "AC06", KeyboardKey::H );
    addMapping( "AD08", KeyboardKey::I );
    addMapping( "AC07", KeyboardKey::J );
    addMapping( "AC08", KeyboardKey::K );
    addMapping( "AC09", KeyboardKey::L );
    addMapping( "AB07", KeyboardKey::M );
    addMapping( "AB06", KeyboardKey::N );
    addMapping( "AD09", KeyboardKey::O );
    addMapping( "AD10", KeyboardKey::P );
    addMapping( "AD01", KeyboardKey::Q );
    addMapping( "AD04", KeyboardKey::R );
    addMapping( "AC02", KeyboardKey::S );
    addMapping( "AD05", KeyboardKey::T );
    addMapping( "AD07", KeyboardKey::U );
    addMapping( "AB04", KeyboardKey::V );
    addMapping( "AD02", KeyboardKey::W );
    addMapping( "AB02", KeyboardKey::X );
    addMapping( "AD06", KeyboardKey::Y );
    addMapping( "AB01", KeyboardKey::Z );
    addMapping( "TLDE", KeyboardKey::GraveAccent );
    addMapping( "AE11", KeyboardKey::Minus );
    addMapping( "AE12", KeyboardKey::Equals );
    addMapping( "AD11", KeyboardKey::LeftBracket );
    addMapping( "AD12", KeyboardKey::RightBracket );
    addMapping( "AC10", KeyboardKey::Semicolon );
    addMapping( "AB08", KeyboardKey::Comma );
    addMapping( "AB09", KeyboardKey::Period );
    addMapping( "AB10", KeyboardKey::Slash );
    addMapping( "BKSL", KeyboardKey::Backslash );
    addMapping( "AC11", KeyboardKey::Apostrophe );
    addMapping( "RTRN", KeyboardKey::Enter );
    addMapping( "SPCE", KeyboardKey::Space );
    addMapping( "TAB",  KeyboardKey::Tab );
    addMapping( "BKSP", KeyboardKey::Backspace );
    addMapping( "DELE", KeyboardKey::Delete );
    addMapping( "INS",  KeyboardKey::Insert );
    addMapping( "LEFT", KeyboardKey::Left );
    addMapping( "RGHT", KeyboardKey::Right );
    addMapping( "UP",   KeyboardKey::Up );
    addMapping( "DOWN", KeyboardKey::Down );
    addMapping( "HOME", KeyboardKey::Home );
    addMapping( "END",  KeyboardKey::End );
    addMapping( "PGUP", KeyboardKey::PageUp );
    addMapping( "PGDN", KeyboardKey::PageDown );
    addMapping( "LFSH", KeyboardKey::LeftShift );
    addMapping( "RTSH", KeyboardKey::RightShift );
    addMapping( "LCTL", KeyboardKey::LeftControl );
    addMapping( "RCTL", KeyboardKey::RightControl );
    addMapping( "LALT", KeyboardKey::LeftAlter );
    addMapping( "RALT", KeyboardKey::RightAlter );
    addMapping( "NMLK", KeyboardKey::NumLock );
    addMapping( "KP0",  KeyboardKey::Keypad0 );
    addMapping( "KP1",  KeyboardKey::Keypad1 );
    addMapping( "KP2",  KeyboardKey::Keypad2 );
    addMapping( "KP3",  KeyboardKey::Keypad3 );
    addMapping( "KP4",  KeyboardKey::Keypad4 );
    addMapping( "KP5",  KeyboardKey::Keypad5 );
    addMapping( "KP6",  KeyboardKey::Keypad6 );
    addMapping( "KP7",  KeyboardKey::Keypad7 );
    addMapping( "KP8",  KeyboardKey::Keypad8 );
    addMapping( "KP9",  KeyboardKey::Keypad9 );
    addMapping( "KPDV", KeyboardKey::KeypadSlash );
    addMapping( "KPMU", KeyboardKey::KeypadAsterisk );
    addMapping( "KPSU", KeyboardKey::KeypadMinus );
    addMapping( "KPAD", KeyboardKey::KeypadPlus );
    addMapping( "KPEN", KeyboardKey::KeypadEnter );
    addMapping( "KPDL", KeyboardKey::KeypadDelete );
    addMapping( "CAPS", KeyboardKey::CapsLock );
    addMapping( "SCLK", KeyboardKey::ScrollLock );
    addMapping( "PRSC", KeyboardKey::PrintScreen );
    addMapping( "PAUS", KeyboardKey::Pause );
    addMapping( "LWIN", KeyboardKey::LeftCommand );
    addMapping( "RWIN", KeyboardKey::RightCommand );
    addMapping( "COMP", KeyboardKey::Menu );
}

}
