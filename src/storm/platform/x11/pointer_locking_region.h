#pragma once

#include <xcb/xcb.h>
#include <xcb/xfixes.h>

#include <storm/rectangle.h>

namespace storm {

class PointerLockingRegion {
public:
    PointerLockingRegion(
        xcb_connection_t *connection,
        xcb_window_t window,
        Rectangle area );

    PointerLockingRegion(
        const PointerLockingRegion& ) = delete;
    PointerLockingRegion& operator = (
        const PointerLockingRegion& ) = delete;

    ~PointerLockingRegion();

private:
    xcb_connection_t *_connection;

    xcb_xfixes_barrier_t _left   = {};
    xcb_xfixes_barrier_t _right  = {};
    xcb_xfixes_barrier_t _top    = {};
    xcb_xfixes_barrier_t _bottom = {};
};

}
