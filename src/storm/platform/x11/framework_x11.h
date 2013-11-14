#pragma once

#include <X11/Xlib.h>

#include <storm/framework.h>
#include <storm/noncopyable.h>

namespace storm {

class FrameworkX11 : public Framework {
    NONCOPYABLE( FrameworkX11 );
public:
    static FrameworkX11* getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

private:
    FrameworkX11();

    Display *_display;
};

}
