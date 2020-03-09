#include <storm/x11/xcb_connection.h>

#include <storm/exception.h>
#include <storm/x11/xcb_pointer.h>

namespace storm {

XcbConnection::XcbConnection() {
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

XcbConnection::~XcbConnection() {
    xcb_disconnect( _connection );
}

XcbConnection::XcbConnection( XcbConnection &&connection ) {
    *this = std::move( connection );
}

XcbConnection& XcbConnection::operator = ( XcbConnection &&connection ) {
    this->~XcbConnection();

    _connection = connection._connection;
    _screen = connection._screen;

    connection._connection = nullptr;
    connection._screen = nullptr;

    return *this;
}

XcbConnection::operator xcb_connection_t* () const {
    return _connection;
}

xcb_screen_t* XcbConnection::getDefaultScreen() const {
    return _screen;
}

xcb_atom_t XcbConnection::getAtom( std::string_view id ) const {
    const xcb_intern_atom_cookie_t request = xcb_intern_atom_unchecked(
        _connection, /* only_if_exists */ 0, id.size(), id.data() );

    const XcbPointer<xcb_intern_atom_reply_t> reply =
        xcb_intern_atom_reply( _connection, request, nullptr );

    return reply ? reply->atom : XCB_ATOM_NONE;
}

XcbConnection XcbConnection::create() {
    XcbConnection connection;

    if( xcb_connection_has_error(connection._connection) ) {
        throw SystemRequirementsNotMet() << "An X server is unavailable";
    }

    return connection;
}

}
