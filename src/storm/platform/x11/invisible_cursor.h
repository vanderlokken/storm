#pragma once

#include <xcb/xcb.h>

namespace storm {

class InvisibleCursor {
public:
    InvisibleCursor(xcb_connection_t *connection, xcb_screen_t *screen);
    ~InvisibleCursor();

    InvisibleCursor(
        const InvisibleCursor&) = delete;
    InvisibleCursor& operator = (
        const InvisibleCursor&) = delete;

    xcb_cursor_t getHandle() const;

private:
    xcb_connection_t *_connection = nullptr;
    xcb_cursor_t _handle = XCB_CURSOR_NONE;
};

}
