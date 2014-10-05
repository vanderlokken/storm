#pragma once

#include <X11/Xlib.h>

#include <storm/keyboard_common.h>
#include <storm/platform/x11/event_loop_x11.h>

namespace storm {

class KeyboardX11 : public KeyboardCommon {
public:
    KeyboardX11( Display *display, Window window );

private:
    void onKeyEvent( const XEvent &event );

    EventLoopX11::Listener _eventListener;
};

}
