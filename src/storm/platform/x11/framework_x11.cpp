#include <storm/platform/x11/framework_x11.h>

#include <memory>

#include <storm/platform/x11/display_connection_x11.h>
#include <storm/throw_exception.h>

namespace storm {

FrameworkX11::FrameworkX11() :
    _display( DisplayConnectionX11::getInstance()->getHandle() )
{
    return;
}

void FrameworkX11::run( const Callback &callback ) {
    storm_assert( callback );

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

            auto eventCallbackIterator = _eventCallbacks.find( event.type );
            if( eventCallbackIterator != _eventCallbacks.end() )
                eventCallbackIterator->second( event );

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

void FrameworkX11::setEventCallback(
    int eventType, const EventCallback &eventCallback )
{
    _eventCallbacks[eventType] = eventCallback;
}

void FrameworkX11::removeEventCallback(
    int eventType )
{
    _eventCallbacks.erase( eventType );
}

FrameworkX11* FrameworkX11::getInstance() {
    static const std::unique_ptr<FrameworkX11> instance( new FrameworkX11 );
    return instance.get();
}

Framework* Framework::getInstance() {
    return FrameworkX11::getInstance();
}

}
