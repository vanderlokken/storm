#include <storm/platform/x11/invisible_cursor.h>

namespace storm {

InvisibleCursor::InvisibleCursor(
        xcb_connection_t *connection, xcb_screen_t *screen ) :
    _connection( connection ),
    _handle( xcb_generate_id(_connection) )
{
    const xcb_pixmap_t pixmap = xcb_generate_id( _connection );

    xcb_create_pixmap(
        _connection,
        1, // bits per pixel
        pixmap,
        screen->root,
        1, // width
        1  // height
    );

    xcb_create_cursor(
        _connection,
        _handle,
        pixmap,
        pixmap,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0 );

    xcb_free_pixmap( _connection, pixmap );
}

InvisibleCursor::~InvisibleCursor() {
    xcb_free_cursor( _connection, _handle );
}

xcb_cursor_t InvisibleCursor::getHandle() const {
    return _handle;
}

}
