#include <storm/platform/x11/rendering_window_x11.h>

#include <cstdint>
#include <memory>

#include <X11/Xutil.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

RenderingWindowX11::RenderingWindowX11( Display *display ) :
    _handle( None ), _display( display ), _fullscreen( false )
{
    const int defaultScreen = ::XDefaultScreen( _display );

    const Window parentWindow = ::XRootWindow( _display, defaultScreen );
    const int x = 0;
    const int y = 0;
    const unsigned int width = 1;
    const unsigned int height = 1;
    const unsigned int borderWidth = 1;
    const unsigned long borderColor =
        ::XBlackPixel( _display, defaultScreen );
    const unsigned long backgroundColor =
        ::XWhitePixel( _display, defaultScreen );

    _handle = ::XCreateSimpleWindow( _display, parentWindow,
        x, y, width, height, borderWidth, borderColor, backgroundColor );
    if( _handle == None )
        throwRuntimeError( "::XCreateSimpleWindow has failed" );

    const long eventMask = FocusChangeMask | PropertyChangeMask;

    if( !::XSelectInput(_display, _handle, eventMask) )
        throwRuntimeError( "::XSelectInput has failed" );

    installShutdownHandler();
    installFocusHandlers();
    installStateChangeHandlers();
}

RenderingWindowX11::~RenderingWindowX11() {
    ::XDestroyWindow( _display, _handle );
}

void RenderingWindowX11::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void RenderingWindowX11::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

Dimensions RenderingWindowX11::getDimensions() const {
    return _dimensions;
}

bool RenderingWindowX11::isActive() const {
    Window activeWindow = None;
    int focusState = 0;

    ::XGetInputFocus( _display, &activeWindow, &focusState );
    return activeWindow == _handle;
}

bool RenderingWindowX11::isFullscreen() const {
    return _fullscreen;
}

void RenderingWindowX11::setWindowed( Dimensions windowDimensions ) {
    ::XUnmapWindow( _display, _handle );
    ::XResizeWindow( _display, _handle,
        windowDimensions.width, windowDimensions.height );
    ::XMapWindow( _display, _handle );
    ::XFlush( _display );

    _dimensions = windowDimensions;
    _fullscreen = false;

    // Try to forbid resizing.
    if( XSizeHints *sizeHints = ::XAllocSizeHints() ) {
        sizeHints->flags = PMinSize | PMaxSize;
        sizeHints->min_width = sizeHints->max_width =
            static_cast<int>( windowDimensions.width );
        sizeHints->min_height = sizeHints->max_height =
            static_cast<int>( windowDimensions.height );
        ::XSetWMNormalHints( _display, _handle, sizeHints );
        ::XFree( sizeHints );
    }
}

void RenderingWindowX11::setFullscreen() {
    throwNotImplemented();
}

Window RenderingWindowX11::getHandle() const {
    return _handle;
}

void RenderingWindowX11::installShutdownHandler() {
    Atom windowDestructionAtom = ::XInternAtom(
        _display, "WM_DELETE_WINDOW", /*onlyExisting = */ false );
    if( windowDestructionAtom == None )
        throwRuntimeError( "::XInternAtom has failed" );

    const Status result = ::XSetWMProtocols(
        _display, _handle, &windowDestructionAtom, /*count = */ 1 );
    if( !result )
        throwRuntimeError( "::XSetWMProtocols has failed" );

    _eventListener.onEvent[ClientMessage] = [=]( const XEvent &event ) {
        if( static_cast<Atom>(event.xclient.data.l[0]) ==
            windowDestructionAtom )
        {
            _observers.notify( &Observer::onShutdown );
            EventLoop::getInstance()->stop();
        }
    };
}

void RenderingWindowX11::installFocusHandlers() {
    _eventListener.onEvent[FocusIn] = [this]( const XEvent &event ) {
        if( event.xfocus.mode != NotifyGrab &&
            event.xfocus.mode != NotifyUngrab )
            _observers.notify( &Observer::onFocusIn );
    };

    _eventListener.onEvent[FocusOut] = [this]( const XEvent &event ) {
        if( event.xfocus.mode != NotifyGrab &&
            event.xfocus.mode != NotifyUngrab )
            _observers.notify( &Observer::onFocusOut );
    };
}

void RenderingWindowX11::installStateChangeHandlers() {
    Atom windowStateAtom = ::XInternAtom(
        _display, "WM_STATE", /*onlyExisting = */ false );
    if( windowStateAtom == None )
        throwRuntimeError( "::XInternAtom has failed" );

    _eventListener.onEvent[PropertyNotify] = [=]( const XEvent &event ) {
        if( event.xproperty.atom == windowStateAtom &&
            event.xproperty.state == PropertyNewValue )
        {
            const long offset = 0;
            const long length = 2; // The number of 32-bit fields
            const Bool shouldDelete = false;

            // Returned values
            Atom format;
            int type;
            unsigned long itemNumber;
            unsigned long remainingBytes;

            struct State {
                uint32_t state;
                uint32_t icon;
            } *state = nullptr;

            ::XGetWindowProperty(
                _display,
                _handle,
                windowStateAtom,
                offset,
                length,
                shouldDelete,
                windowStateAtom,
                &format,
                &type,
                &itemNumber,
                &remainingBytes,
                reinterpret_cast<unsigned char**>(&state) );

            if( state ) {
                if( state->state == NormalState )
                    _observers.notify( &Observer::onUnfolding );
                else if( state->state == IconicState )
                    _observers.notify( &Observer::onFolding );
                ::XFree( state );
            }
        }
    };
}

RenderingWindowX11* RenderingWindowX11::getInstance() {
    static const std::unique_ptr<RenderingWindowX11> instance(
        new RenderingWindowX11(getDisplayHandleX11()) );
    return instance.get();
}

RenderingWindow* RenderingWindow::getInstance() {
    return RenderingWindowX11::getInstance();
}

}
