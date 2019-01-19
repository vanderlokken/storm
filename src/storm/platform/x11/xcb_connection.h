#pragma once

#include <string_view>

#include <xcb/xcb.h>

namespace storm {

class XcbConnection {
public:
    static XcbConnection create();

    ~XcbConnection();

    XcbConnection(
        const XcbConnection& ) = delete;
    XcbConnection& operator = (
        const XcbConnection& ) = delete;

    XcbConnection(
        XcbConnection &&connection );
    XcbConnection& operator = (
        XcbConnection &&connection );

    operator xcb_connection_t* () const;

    xcb_screen_t* getDefaultScreen() const;
    xcb_atom_t getAtom(std::string_view id) const;

private:
    XcbConnection();

    xcb_connection_t *_connection = nullptr;
    xcb_screen_t *_screen = nullptr;
};

}
