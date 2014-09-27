#pragma once

#include <X11/Xlib.h>

#include <storm/noncopyable.h>

namespace storm {

class DisplayConnectionX11 {
    NONCOPYABLE( DisplayConnectionX11 );
public:
    static DisplayConnectionX11* getInstance();

    ~DisplayConnectionX11();

    Display* getHandle() const;

private:
    DisplayConnectionX11();

    Display *_handle;
};

}
