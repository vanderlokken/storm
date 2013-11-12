#pragma once

#include <X11/Xlib.h>

#include "Framework.h"
#include "Noncopyable.h"

namespace storm {

class FrameworkX11 : public Framework {
    NONCOPYABLE( FrameworkX11 );
public:
    static std::shared_ptr<FrameworkX11> getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

private:
    FrameworkX11();

    Display *_display;
};

}
