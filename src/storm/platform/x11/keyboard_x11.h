#pragma once

#include <X11/Xlib.h>

#include <storm/keyboard_common.h>

namespace storm {

class KeyboardX11 : public KeyboardCommon {
public:
    KeyboardX11();

private:
    void onEvent( const XEvent &event );
};

}
