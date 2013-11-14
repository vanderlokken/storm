#include <storm/platform/x11/framework_x11.h>

#include <storm/exception.h>
#include <storm/platform/x11/display_connection_x11.h>

namespace storm {

FrameworkX11::FrameworkX11()
    : _display( DisplayConnectionX11::getInstance()->getHandle() )
{
    return;
}

void FrameworkX11::run( const Callback &callback ) {
    if( !callback )
        throwInvalidArgument( "'callback' is invalid" );

    const bool getOnlyExistingAtoms = true;

    const Atom windowDestructionAtom = ::XInternAtom(
        _display, "WM_DELETE_WINDOW", getOnlyExistingAtoms );

    if( windowDestructionAtom == None ) {
        throwRuntimeError( "::XInternAtom has failed" );
    }

    bool processing = true;

    while( processing ) {
        const int pendingEventCount = ::XPending( _display );

        for( int i = 0; i < pendingEventCount; ++i ) {
            XEvent event;
            ::XNextEvent( _display, &event );

            if( event.type == ClientMessage &&
                    event.xclient.data.l[0] == windowDestructionAtom ) {
                processing = false;
            }
        }

        if( !processing )
            break;

        callback();
    }
    return;
}

void FrameworkX11::stop() {
    throwRuntimeError( "Not implemented" );
    // XSendEvent
    return;
}

std::shared_ptr<FrameworkX11> FrameworkX11::getInstance() {
    static const std::shared_ptr<FrameworkX11> instance( new FrameworkX11 );
    return instance;
}

std::shared_ptr<Framework> Framework::getInstance() {
    return FrameworkX11::getInstance();
}

}
