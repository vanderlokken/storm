#pragma once

#include <unordered_map>

#include <xcb/xcb.h>

#include <storm/input.h>

namespace storm {

std::unordered_map<xcb_keycode_t, KeyboardKey> createKeycodeMapping(
    xcb_connection_t *connection);

}
