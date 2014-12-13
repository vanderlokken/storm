#include <storm/platform/x11/display_connection_x11.h>

#include <storm/throw_exception.h>

namespace storm {

namespace {

struct DisplayX11 {
    DisplayX11() :
        handle( ::XOpenDisplay(/* displayName = */ nullptr) )
    {
        if( !handle )
            throwRuntimeError( "::XOpenDisplay has failed" );
    }

    ~DisplayX11() {
        ::XCloseDisplay( handle );
    }

    XDisplay *handle;
};

}

XDisplay* getDisplayHandleX11() {
    static const DisplayX11 display;
    return display.handle;
}

}
