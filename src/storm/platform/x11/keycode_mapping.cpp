#include <storm/platform/x11/keycode_mapping.h>

#include <climits>
#include <optional>

#define XK_LATIN1
#define XK_MISCELLANY
#include <X11/keysymdef.h>

#include <storm/platform/x11/xcb_pointer.h>

namespace storm {

namespace {

std::optional<KeyboardKey> convertKeysym(xcb_keysym_t keysym) {
    switch( keysym ) {
    case XK_Escape:       return KeyboardKey::Escape;
    case XK_F1:           return KeyboardKey::F1;
    case XK_F2:           return KeyboardKey::F2;
    case XK_F3:           return KeyboardKey::F3;
    case XK_F4:           return KeyboardKey::F4;
    case XK_F5:           return KeyboardKey::F5;
    case XK_F6:           return KeyboardKey::F6;
    case XK_F7:           return KeyboardKey::F7;
    case XK_F8:           return KeyboardKey::F8;
    case XK_F9:           return KeyboardKey::F9;
    case XK_F10:          return KeyboardKey::F10;
    case XK_F11:          return KeyboardKey::F11;
    case XK_F12:          return KeyboardKey::F12;
    case XK_0:            return KeyboardKey::Digit0;
    case XK_1:            return KeyboardKey::Digit1;
    case XK_2:            return KeyboardKey::Digit2;
    case XK_3:            return KeyboardKey::Digit3;
    case XK_4:            return KeyboardKey::Digit4;
    case XK_5:            return KeyboardKey::Digit5;
    case XK_6:            return KeyboardKey::Digit6;
    case XK_7:            return KeyboardKey::Digit7;
    case XK_8:            return KeyboardKey::Digit8;
    case XK_9:            return KeyboardKey::Digit9;
    case XK_a:            return KeyboardKey::A;
    case XK_b:            return KeyboardKey::B;
    case XK_c:            return KeyboardKey::C;
    case XK_d:            return KeyboardKey::D;
    case XK_e:            return KeyboardKey::E;
    case XK_f:            return KeyboardKey::F;
    case XK_g:            return KeyboardKey::G;
    case XK_h:            return KeyboardKey::H;
    case XK_i:            return KeyboardKey::I;
    case XK_j:            return KeyboardKey::J;
    case XK_k:            return KeyboardKey::K;
    case XK_l:            return KeyboardKey::L;
    case XK_m:            return KeyboardKey::M;
    case XK_n:            return KeyboardKey::N;
    case XK_o:            return KeyboardKey::O;
    case XK_p:            return KeyboardKey::P;
    case XK_q:            return KeyboardKey::Q;
    case XK_r:            return KeyboardKey::R;
    case XK_s:            return KeyboardKey::S;
    case XK_t:            return KeyboardKey::T;
    case XK_u:            return KeyboardKey::U;
    case XK_v:            return KeyboardKey::V;
    case XK_w:            return KeyboardKey::W;
    case XK_x:            return KeyboardKey::X;
    case XK_y:            return KeyboardKey::Y;
    case XK_z:            return KeyboardKey::Z;
    case XK_grave:        return KeyboardKey::GraveAccent;
    case XK_minus:        return KeyboardKey::Minus;
    case XK_equal:        return KeyboardKey::Equals;
    case XK_bracketleft:  return KeyboardKey::LeftBracket;
    case XK_bracketright: return KeyboardKey::RightBracket;
    case XK_semicolon:    return KeyboardKey::Semicolon;
    case XK_comma:        return KeyboardKey::Comma;
    case XK_period:       return KeyboardKey::Period;
    case XK_slash:        return KeyboardKey::Slash;
    case XK_backslash:    return KeyboardKey::Backslash;
    case XK_apostrophe:   return KeyboardKey::Apostrophe;
    case XK_Return:       return KeyboardKey::Enter;
    case XK_space:        return KeyboardKey::Space;
    case XK_Tab:          return KeyboardKey::Tab;
    case XK_BackSpace:    return KeyboardKey::Backspace;
    case XK_Delete:       return KeyboardKey::Delete;
    case XK_Insert:       return KeyboardKey::Insert;
    case XK_Left:         return KeyboardKey::Left;
    case XK_Right:        return KeyboardKey::Right;
    case XK_Up:           return KeyboardKey::Up;
    case XK_Down:         return KeyboardKey::Down;
    case XK_Home:         return KeyboardKey::Home;
    case XK_End:          return KeyboardKey::End;
    case XK_Page_Up:      return KeyboardKey::PageUp;
    case XK_Page_Down:    return KeyboardKey::PageDown;
    case XK_Shift_L:      return KeyboardKey::LeftShift;
    case XK_Shift_R:      return KeyboardKey::RightShift;
    case XK_Control_L:    return KeyboardKey::LeftControl;
    case XK_Control_R:    return KeyboardKey::RightControl;
    case XK_Alt_L:        return KeyboardKey::LeftAlter;
    case XK_Alt_R:        return KeyboardKey::RightAlter;
    case XK_Num_Lock:     return KeyboardKey::NumLock;
    case XK_KP_Insert:    return KeyboardKey::Keypad0;
    case XK_KP_End:       return KeyboardKey::Keypad1;
    case XK_KP_Down:      return KeyboardKey::Keypad2;
    case XK_KP_Next:      return KeyboardKey::Keypad3;
    case XK_KP_Left:      return KeyboardKey::Keypad4;
    case XK_KP_Begin:     return KeyboardKey::Keypad5;
    case XK_KP_Right:     return KeyboardKey::Keypad6;
    case XK_KP_Home:      return KeyboardKey::Keypad7;
    case XK_KP_Up:        return KeyboardKey::Keypad8;
    case XK_KP_Prior:     return KeyboardKey::Keypad9;
    case XK_KP_Divide:    return KeyboardKey::KeypadSlash;
    case XK_KP_Multiply:  return KeyboardKey::KeypadAsterisk;
    case XK_KP_Subtract:  return KeyboardKey::KeypadMinus;
    case XK_KP_Add:       return KeyboardKey::KeypadPlus;
    case XK_KP_Enter:     return KeyboardKey::KeypadEnter;
    case XK_KP_Delete:    return KeyboardKey::KeypadDelete;
    case XK_Caps_Lock:    return KeyboardKey::CapsLock;
    case XK_Scroll_Lock:  return KeyboardKey::ScrollLock;
    case XK_Print:        return KeyboardKey::PrintScreen;
    case XK_Pause:        return KeyboardKey::Pause;
    case XK_Super_L:      return KeyboardKey::LeftCommand;
    case XK_Super_R:      return KeyboardKey::RightCommand;
    case XK_Menu:         return KeyboardKey::Menu;
    }

    return std::nullopt;
}

} // namespace

std::unordered_map<xcb_keycode_t, KeyboardKey> createKeycodeMapping(
    xcb_connection_t *connection)
{
    const xcb_setup_t *setup = xcb_get_setup( connection );

    const uint8_t numKeycodes = setup->max_keycode - setup->min_keycode + 1;

    const xcb_get_keyboard_mapping_cookie_t request =
        xcb_get_keyboard_mapping_unchecked(
            connection, setup->min_keycode, numKeycodes );

    const XcbPointer<xcb_get_keyboard_mapping_reply_t> reply =
        xcb_get_keyboard_mapping_reply( connection, request, nullptr );

    std::unordered_map<xcb_keycode_t, KeyboardKey> mapping;

    if( !reply ) {
        return mapping;
    }

    const xcb_keysym_t *keysym = xcb_get_keyboard_mapping_keysyms( reply );

    for( uint8_t keycodeIndex = 0;
            keycodeIndex < numKeycodes; ++keycodeIndex ) {
        if( std::optional<KeyboardKey> key = convertKeysym(*keysym) ) {
            mapping[setup->min_keycode + keycodeIndex] = *key;
        }

        keysym += reply->keysyms_per_keycode;
    }

    return mapping;
}

}
