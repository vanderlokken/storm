#pragma once

#include <xcb/xcb.h>

#include <storm/exception.h>

namespace storm {

class XcbConnection {
public:
    static XcbConnection create() {
        XcbConnection connection;

        if( xcb_connection_has_error(connection._connection) ) {
            throw SystemRequirementsNotMet() << "An X server is unavailable";
        }

        return std::move( connection );
    }

    ~XcbConnection() {
        xcb_disconnect( _connection );
    }

    XcbConnection(
        const XcbConnection& ) = delete;
    XcbConnection& operator = (
        const XcbConnection& ) = delete;

    XcbConnection( XcbConnection &&connection ) {
        *this = std::move( connection );
    }

    XcbConnection& operator = ( XcbConnection &&connection ) {
        xcb_disconnect( _connection );

        _connection = connection._connection;
        _screen = connection._screen;

        connection._connection = nullptr;
        connection._screen = nullptr;

        return *this;
    }

    operator xcb_connection_t* () const {
        return _connection;
    }

    xcb_screen_t* getDefaultScreen() const {
        return _screen;
    }

private:
    XcbConnection() {
        int screenIndex = 0;

        _connection = xcb_connect( nullptr, &screenIndex );

        xcb_screen_iterator_t iterator =
            xcb_setup_roots_iterator( xcb_get_setup(_connection) );

        for( int screen = 0; screen < screenIndex; ++screen ) {
            if( iterator.rem ) {
                xcb_screen_next( &iterator );
            }
        }

        _screen = iterator.data;
    }

    xcb_connection_t *_connection = nullptr;
    xcb_screen_t *_screen = nullptr;
};

}
