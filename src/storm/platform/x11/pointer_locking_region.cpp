#include <storm/platform/x11/pointer_locking_region.h>

#include <climits>

namespace storm {

PointerLockingRegion::PointerLockingRegion(
        xcb_connection_t *connection,
        xcb_window_t window,
        Rectangle area ) :
    _connection( connection ),
    _left( xcb_generate_id(_connection) ),
    _right( xcb_generate_id(_connection) ),
    _top( xcb_generate_id(_connection) ),
    _bottom( xcb_generate_id(_connection) )
{
    // The following code uses the 'INT16_MIN' and 'INT16_MAX' constants
    // instead of making an exact bounding box due to the following bug in
    // X.Org Server: https://gitlab.freedesktop.org/xorg/xserver/issues/606

    xcb_xfixes_create_pointer_barrier(
        _connection,
        _left,
        window,
        area.x,
        INT16_MIN,
        area.x,
        INT16_MAX,
        XCB_XFIXES_BARRIER_DIRECTIONS_POSITIVE_X,
        0,
        nullptr );

    xcb_xfixes_create_pointer_barrier(
        _connection,
        _right,
        window,
        area.getRight(),
        INT16_MIN,
        area.getRight(),
        INT16_MAX,
        XCB_XFIXES_BARRIER_DIRECTIONS_NEGATIVE_X,
        0,
        nullptr );

    xcb_xfixes_create_pointer_barrier(
        _connection,
        _top,
        window,
        INT16_MIN,
        area.y,
        INT16_MAX,
        area.y,
        XCB_XFIXES_BARRIER_DIRECTIONS_POSITIVE_Y,
        0,
        nullptr );

    xcb_xfixes_create_pointer_barrier(
        _connection,
        _bottom,
        window,
        INT16_MIN,
        area.getBottom(),
        INT16_MAX,
        area.getBottom(),
        XCB_XFIXES_BARRIER_DIRECTIONS_NEGATIVE_Y,
        0,
        nullptr );
}

PointerLockingRegion::~PointerLockingRegion() {
    xcb_xfixes_delete_pointer_barrier( _connection, _left );
    xcb_xfixes_delete_pointer_barrier( _connection, _right );
    xcb_xfixes_delete_pointer_barrier( _connection, _top );
    xcb_xfixes_delete_pointer_barrier( _connection, _bottom );
}

}
