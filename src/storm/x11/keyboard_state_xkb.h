#pragma once

#include <optional>
#include <unordered_map>

// The following header uses the 'explicit' identifier as a structure member
// name.
#define explicit xcb_explicit
#include <xcb/xkb.h>
#undef explicit
#include <xcb/xcb.h>

#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-x11.h>

#include <storm/input.h>

namespace storm {

class KeyboardStateXkb {
public:
    explicit KeyboardStateXkb( xcb_connection_t *connection );
    ~KeyboardStateXkb();

    KeyboardStateXkb(
        const KeyboardStateXkb& ) = delete;
    KeyboardStateXkb& operator = (
        const KeyboardStateXkb& ) = delete;

    std::optional<KeyboardKey> getKey( xkb_keycode_t keycode ) const;
    std::optional<char32_t> getCharacter( xkb_keycode_t keycode ) const;

    void update( const xcb_xkb_state_notify_event_t &event ) const;

private:
    void selectEvents( int32_t deviceId );
    void updateKeycodeMapping();

    xcb_connection_t *_connection = nullptr;
    xkb_context *_context = nullptr;
    xkb_keymap *_keymap = nullptr;
    xkb_state *_state = nullptr;

    std::unordered_map<xkb_keycode_t, KeyboardKey> _keycodeMapping;
};

}
