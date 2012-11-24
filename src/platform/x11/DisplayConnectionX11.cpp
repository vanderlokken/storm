#include "DisplayConnectionX11.h"

#include "Exception.h"

namespace storm {

DisplayConnectionX11::DisplayConnectionX11()
    : _handle( nullptr )
{
    char *displayName = nullptr;

    _handle = ::XOpenDisplay( displayName );

    if( !_handle ) {
        throwRuntimeError( "::XOpenDisplay has failed" );
    }
    return;
}

DisplayConnectionX11::~DisplayConnectionX11() noexcept {
    ::XCloseDisplay( _handle );
    return;
}

Display* DisplayConnectionX11::getHandle() const noexcept {
    return _handle;
}

std::shared_ptr<DisplayConnectionX11> DisplayConnectionX11::getInstance() {
    static const std::shared_ptr<DisplayConnectionX11> instance( new DisplayConnectionX11 );
    return instance;
}

}