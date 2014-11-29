#pragma once

#include <iconv.h>

#include <X11/Xlib.h>

#include <storm/keyboard_common.h>
#include <storm/noncopyable.h>
#include <storm/platform/x11/event_loop_x11.h>
#include <storm/platform/x11/rendering_window_x11.h>

namespace storm {

class CharacterConversionDescriptor {
    NONCOPYABLE( CharacterConversionDescriptor );
public:
    CharacterConversionDescriptor(
        const char *fromEncoding, const char *toEncoding );
    ~CharacterConversionDescriptor();

    operator iconv_t () const {
        return _descriptor;
    }
private:
    iconv_t _descriptor;
};

class InputMethodHandleX11 {
    NONCOPYABLE( InputMethodHandleX11 );
public:
    explicit InputMethodHandleX11( Display *display );
    ~InputMethodHandleX11();

    operator XIM () const {
        return _handle;
    }
private:
    XIM _handle;
};

class InputContextHandleX11 {
    NONCOPYABLE( InputContextHandleX11 );
public:
    InputContextHandleX11(
        XIM inputMethod, XIMStyle inputStyle, Window window );
    ~InputContextHandleX11();

    operator XIC () const {
        return _handle;
    }
private:
    XIC _handle;
};

class KeyboardX11 : public KeyboardCommon {
public:
    explicit KeyboardX11( RenderingWindowX11* );

private:
    void onKeyEvent( const XEvent &event );

    CharacterConversionDescriptor _utf32ConversionDescriptor;

    InputMethodHandleX11 _inputMethodHandle;
    InputContextHandleX11 _inputContextHandle;

    EventLoopX11::Listener _eventListener;
};

}
