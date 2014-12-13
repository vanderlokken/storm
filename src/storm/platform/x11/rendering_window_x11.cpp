#include <storm/platform/x11/rendering_window_x11.h>

#include <cstdint>
#include <memory>

#include <X11/Xutil.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

namespace{
// The following values are taken from the "Extended Window Manager Hints"
// document. See http://standards.freedesktop.org/wm-spec/wm-spec-latest.html
const long _NET_WM_STATE_REMOVE = 0;
const long _NET_WM_STATE_ADD = 1;
const long _NET_WM_STATE_TOGGLE = 2;
}

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

    addEventMask( FocusChangeMask | PropertyChangeMask );

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
    XWindowAttributes windowAttributes = {};
    ::XGetWindowAttributes( _display, _handle, &windowAttributes );
    return {
        static_cast<unsigned int>(windowAttributes.width),
        static_cast<unsigned int>(windowAttributes.height)
    };
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
    setDimensionsConstraint( &windowDimensions );
    setFullscreen( false );

    ::XResizeWindow(
        _display, _handle, windowDimensions.width, windowDimensions.height );

    ::XMapWindow( _display, _handle );

    _fullscreen = false;
}

void RenderingWindowX11::setFullscreen( FullscreenMode fullscreenMode ) {
    if( fullscreenMode.custom )
        throwNotImplemented();

    setDimensionsConstraint( nullptr );
    setFullscreen( true );

    ::XMapWindow( _display, _handle );

    _fullscreen = true;
}

Window RenderingWindowX11::getHandle() const {
    return _handle;
}

void RenderingWindowX11::addEventMask( unsigned long eventMask ) {
    XWindowAttributes windowAttributes = {};

    if( !::XGetWindowAttributes(_display, _handle, &windowAttributes) )
        throwRuntimeError( "::XGetWindowAttributes has failed" );

    windowAttributes.your_event_mask |= eventMask;

    if( !::XSelectInput(_display, _handle, windowAttributes.your_event_mask) )
        throwRuntimeError( "::XSelectInput has failed" );
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
            const Atom type = windowStateAtom;

            // Returned values
            Atom actualType;
            int actualFormat;
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
                type,
                &actualType,
                &actualFormat,
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

void RenderingWindowX11::setFullscreen( bool fullscreen ) {
    static Atom windowStateAtom = ::XInternAtom(
        _display, "_NET_WM_STATE", /*onlyExisting = */ false );
    static Atom windowStateFullscreenAtom = ::XInternAtom(
        _display, "_NET_WM_STATE_FULLSCREEN", /*onlyExisting = */ false );

    XEvent event = {};
    event.xclient.type = ClientMessage;
    event.xclient.display = _display;
    event.xclient.window = _handle;
    event.xclient.message_type = windowStateAtom;
    event.xclient.format = 32;
    event.xclient.data.l[0] =
        (fullscreen ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE);
    event.xclient.data.l[1] = windowStateFullscreenAtom;

    ::XSendEvent(
        _display,
        ::XRootWindow(_display, ::XDefaultScreen(_display)),
        /*propagate = */ false,
        /*eventMask = */ SubstructureNotifyMask | SubstructureRedirectMask,
        &event );
}

void RenderingWindowX11::setDimensionsConstraint(
    const Dimensions *dimensions )
{
    if( XSizeHints *sizeHints = ::XAllocSizeHints() ) {
        if( dimensions ) {
            sizeHints->flags = PMinSize | PMaxSize;
            sizeHints->min_width = sizeHints->max_width =
                static_cast<int>( dimensions->width );
            sizeHints->min_height = sizeHints->max_height =
                static_cast<int>( dimensions->height );
        }
        ::XSetWMNormalHints( _display, _handle, sizeHints );
        ::XFree( sizeHints );
    }
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
