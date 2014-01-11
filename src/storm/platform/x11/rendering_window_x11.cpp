#include <storm/platform/x11/rendering_window_x11.h>

#include <memory>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

RenderingWindowX11::RenderingWindowX11()
    : _handle( None ),
      _display( DisplayConnectionX11::getInstance()->getHandle() ),
      _fullscreen( false )
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

    if( windowDestructionAtom == None ) {
        throwRuntimeError( "::XInternAtom has failed" );
    }

    const Status result = ::XSetWMProtocols( _display, _handle, &windowDestructionAtom, 1 );

    if( result == 0 ) {
        throwRuntimeError( "::XSetWMProtocols has failed" );
    }
    return;
}

RenderingWindowX11::~RenderingWindowX11() {
    ::XDestroyWindow( _display, _handle );
    return;
}

Dimensions RenderingWindowX11::getDimensions() const noexcept {
    return _dimensions;
}

bool RenderingWindowX11::isFullscreen() const noexcept {
    return _fullscreen;
}

void RenderingWindowX11::setWindowed( Dimensions windowDimensions ) {
    ::XUnmapWindow( _display, _handle );
    ::XResizeWindow( _display, _handle, windowDimensions.getWidth(), windowDimensions.getHeight() );
    ::XMapWindow( _display, _handle );
    ::XFlush( _display );

    _dimensions = windowDimensions;
    _fullscreen = false;
    return;
}

void RenderingWindowX11::setFullscreen() {
    throwRuntimeError( "Not implemented" );
}

Window RenderingWindowX11::getHandle() const noexcept {
    return _handle;
}

RenderingWindowX11* RenderingWindowX11::getInstance() {
    static const std::unique_ptr<RenderingWindowX11> instance( new RenderingWindowX11 );
    return instance.get();
}

RenderingWindow* RenderingWindow::getInstance() {
    return RenderingWindowX11::getInstance();
}

}
