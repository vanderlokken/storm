#pragma once

#include <X11/Xlib.h>

#include <storm/exception.h>

namespace storm {

class DisplayConnection {
public:
    DisplayConnection() :
        _display( XOpenDisplay(nullptr) )
    {
        if( !_display ) {
            throw SystemRequirementsNotMet() << "An X server is unavailable";
        }
    }

    ~DisplayConnection() {
        XCloseDisplay( _display );
    }

    DisplayConnection(
        const DisplayConnection& ) = delete;
    DisplayConnection& operator = (
        const DisplayConnection& ) = delete;

    operator ::Display* () const {
        return _display;
    }

private:
    ::Display *_display;
};

}
