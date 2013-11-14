#pragma once

#include <memory>

#include <X11/Xlib.h>

namespace storm {

class DisplayConnectionX11 {
public:
    static DisplayConnectionX11* getInstance();

    ~DisplayConnectionX11();

    Display* getHandle() const noexcept;

private:
    DisplayConnectionX11();

    Display *_handle;
};

}
