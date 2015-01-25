#pragma once

#include <functional>

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

#include <storm/noncopyable.h>
#include <storm/platform/x11/display_connection_x11.h>
#include <storm/platform/x11/event_loop_x11.h>

namespace storm {

class InputX11 {
    NONCOPYABLE( InputX11 );
public:
    struct MouseEventListener {
        std::function<void(const XIDeviceEvent&)> onButtonPress;
        std::function<void(const XIDeviceEvent&)> onButtonRelease;
        std::function<void(const XIDeviceEvent&)> onMovement;
        std::function<void(const XIRawEvent&)> onRawMovement;
        std::function<void(const XIEnterEvent&)> onEnter;
        std::function<void(const XILeaveEvent&)> onLeave;
        // std::function<void(const XIFocusInEvent&)> onFocusIn;
        // std::function<void(const XIFocusOutEvent&)> onFocusOut;
    };

    struct KeyboardEventListener {
        std::function<void(const XIDeviceEvent&)> onKeyPress;
        std::function<void(const XIDeviceEvent&)> onKeyRelease;
        // std::function<void(const XIFocusInEvent&)> onFocusIn;
        // std::function<void(const XIFocusOutEvent&)> onFocusOut;
    };

    static InputX11* getInstance();

    void setMouseEventListener( const MouseEventListener* );
    void setKeyboardEventListener( const KeyboardEventListener* );

private:
    InputX11( XDisplay *display, Window window );

    void setEventMask( Window window, unsigned int mask );
    void dispatchEvent( const XIEvent *event );

    int getDeviceId( int deviceType );

    XDisplay *_display;
    Window _window;

    EventLoopX11::Listener _eventListener;

    int _mouseDeviceId;
    int _keyboardDeviceId;

    const MouseEventListener *_mouseEventListener;
    const KeyboardEventListener *_keyboardEventListener;
};

}
