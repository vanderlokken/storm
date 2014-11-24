#pragma once

#include <X11/Xlib.h>

#include <storm/keyboard_common.h>
#include <storm/platform/x11/event_loop_x11.h>
#include <storm/platform/x11/rendering_window_x11.h>

namespace storm {

class KeyboardX11 : public KeyboardCommon {
public:
    explicit KeyboardX11( RenderingWindowX11* );

private:
    void onKeyEvent( const XEvent &event );

    EventLoopX11::Listener _eventListener;
};

}
