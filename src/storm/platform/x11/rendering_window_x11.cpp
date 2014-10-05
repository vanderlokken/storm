#include <storm/platform/x11/rendering_window_x11.h>

#include <memory>

#include <X11/Xutil.h>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

RenderingWindowX11::RenderingWindowX11( Display *display ) :
    _handle( None ), _display( display ), _fullscreen( false )
{
    const Window parentWindow = XRootWindow( _display, DefaultScreen(_display) );
    const int x = 0;
    const int y = 0;
    const unsigned int width = 1;
    const unsigned int height = 1;
    const unsigned int borderWidth = 1;
    const unsigned long borderColor = BlackPixel( _display, DefaultScreen(_display) );
    const unsigned long backgroundColor = WhitePixel( _display, DefaultScreen(_display) );

    _handle = ::XCreateSimpleWindow(
        _display, parentWindow, x, y, width, height, borderWidth, borderColor, backgroundColor );

    if( _handle == None ) {
        throwRuntimeError( "::XCreateSimpleWindow has failed" );
    }

    const bool getOnlyExistingAtoms = true;

    Atom windowDestructionAtom = ::XInternAtom(
        _display, "WM_DELETE_WINDOW", getOnlyExistingAtoms );
    if( windowDestructionAtom == None )
        throwRuntimeError( "::XInternAtom has failed" );

    const Status result = ::XSetWMProtocols(
        _display, _handle, &windowDestructionAtom, 1 );
    if( !result )
        throwRuntimeError( "::XSetWMProtocols has failed" );

    _eventListener.onEvent[ClientMessage] = [=]( const XEvent &event ) {
        if( event.xclient.data.l[0] == windowDestructionAtom )
            EventLoop::getInstance()->stop();
    };
}

RenderingWindowX11::~RenderingWindowX11() {
    ::XDestroyWindow( _display, _handle );
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
    ::XResizeWindow( _display, _handle, windowDimensions.width, windowDimensions.height );
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

RenderingWindowX11* RenderingWindowX11::getInstance() {
    static const std::unique_ptr<RenderingWindowX11> instance(
        new RenderingWindowX11(getDisplayHandleX11()) );
    return instance.get();
}

RenderingWindow* RenderingWindow::getInstance() {
    return RenderingWindowX11::getInstance();
}

}
