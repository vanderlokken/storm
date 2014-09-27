#include <storm/platform/x11/display_connection_x11.h>

#include <memory>

#include <storm/throw_exception.h>

namespace storm {

DisplayConnectionX11::DisplayConnectionX11() :
    _handle( nullptr )
{
    const char *displayName = nullptr;
    _handle = ::XOpenDisplay( displayName );

    if( !_handle )
        throwRuntimeError( "::XOpenDisplay has failed" );
}

DisplayConnectionX11::~DisplayConnectionX11() {
    ::XCloseDisplay( _handle );
}

Display* DisplayConnectionX11::getHandle() const {
    return _handle;
}

DisplayConnectionX11* DisplayConnectionX11::getInstance() {
    static const std::unique_ptr<DisplayConnectionX11> instance( new DisplayConnectionX11 );
    return instance.get();
}

}
