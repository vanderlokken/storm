#include <storm/platform/x11/input_x11.h>

#include <memory>

#include <storm/exception.h>
#include <storm/platform/x11/rendering_window_x11.h>

namespace storm {

namespace {

template<class EventType, class Callback>
void dispatch(
    const XIEvent *event,
    const Callback &callback, int deviceId )
{
    const EventType *specificEvent =
        reinterpret_cast<const EventType*>( event );

    if( specificEvent->deviceid == deviceId && callback )
        callback( *specificEvent );
}

} // namespace

InputX11::InputX11( XDisplay *display, Window window ) :
    _display( display ),
    _window( window ),
    _mouseDeviceId( 0 ),
    _keyboardDeviceId( 0 ),
    _mouseEventListener( nullptr ),
    _keyboardEventListener( nullptr )
{
    const char *errorMessage = "XInput2 is not supported by X server";

    int opCode = 0;
    int eventCode = 0;
    int errorCode = 0;
    if( !::XQueryExtension(
            _display, "XInputExtension", &opCode, &eventCode, &errorCode) )
        throw SystemRequirementsNotMet() << errorMessage;

    int majorVersion = 2;
    int minorVersion = 0;
    if( ::XIQueryVersion(_display, &majorVersion, &minorVersion) == BadRequest )
        throw SystemRequirementsNotMet() << errorMessage;

    _mouseDeviceId = getDeviceId( XIMasterPointer );
    _keyboardDeviceId = getDeviceId( XIMasterKeyboard );

    const unsigned int windowEventMask =
        XI_KeyPressMask |
        XI_KeyReleaseMask |
        XI_ButtonPressMask |
        XI_ButtonReleaseMask |
        XI_MotionMask |
        XI_EnterMask |
        XI_LeaveMask |
        XI_FocusInMask |
        XI_FocusOutMask;

    const unsigned int rootWindowEventMask =
        XI_RawMotionMask;

    setEventMask( _window, windowEventMask );
    setEventMask( ::XDefaultRootWindow(_display), rootWindowEventMask );

    _eventListener.onEvent[GenericEvent] = [=]( const XEvent &event ) {
        if( event.xcookie.extension == opCode ) {
            XGenericEventCookie cookieEvent = event.xcookie;
            ::XGetEventData( _display, &cookieEvent );
            dispatchEvent( static_cast<XIEvent*>(cookieEvent.data) );
            ::XFreeEventData( _display, &cookieEvent );
        }
    };
}

void InputX11::setMouseEventListener(
    const MouseEventListener *listener )
{
    _mouseEventListener = listener;
}

void InputX11::setKeyboardEventListener(
    const KeyboardEventListener *listener )
{
    _keyboardEventListener = listener;
}

void InputX11::setEventMask( Window window, unsigned int mask ) {
    XIEventMask eventMask;
    eventMask.deviceid = XIAllMasterDevices;
    eventMask.mask_len = sizeof( mask );
    eventMask.mask = reinterpret_cast<unsigned char*>( &mask );

    const Status result =
        ::XISelectEvents( _display, window, &eventMask, /*maskCount = */ 1 );
    if( result != Success )
        throwRuntimeError( "::XISelectEvents has failed" );
}

void InputX11::dispatchEvent( const XIEvent *event ) {
    if( _keyboardEventListener ) {
        switch( event->evtype ) {
        case XI_KeyPress:
            dispatch<XIDeviceEvent>(
                event, _keyboardEventListener->onKeyPress, _keyboardDeviceId );
            return;
        case XI_KeyRelease:
            dispatch<XIDeviceEvent>(
                event, _keyboardEventListener->onKeyRelease, _keyboardDeviceId );
            return;
        }
    }

    if( _mouseEventListener ) {
        switch( event->evtype ) {
        case XI_ButtonPress:
            dispatch<XIDeviceEvent>(
                event, _mouseEventListener->onButtonPress, _mouseDeviceId );
            return;
        case XI_ButtonRelease:
            dispatch<XIDeviceEvent>(
                event, _mouseEventListener->onButtonRelease, _mouseDeviceId );
            return;
        case XI_Motion:
            dispatch<XIDeviceEvent>(
                event, _mouseEventListener->onMovement, _mouseDeviceId );
            return;
        case XI_RawMotion:
            dispatch<XIRawEvent>(
                event, _mouseEventListener->onRawMovement, _mouseDeviceId );
            return;
        case XI_Enter:
            dispatch<XIEnterEvent>(
                event, _mouseEventListener->onEnter, _mouseDeviceId );
            return;
        case XI_Leave:
            dispatch<XILeaveEvent>(
                event, _mouseEventListener->onLeave, _mouseDeviceId );
            return;
        }
    }
}

int InputX11::getDeviceId( int deviceType ) {
    int deviceId = -1;

    int deviceNumber = 0;
    XIDeviceInfo *devices =
        ::XIQueryDevice( _display, XIAllMasterDevices, &deviceNumber );

    if( !devices )
        throwRuntimeError( "::XIQueryDevice has failed" );

    for( int deviceIndex = 0; deviceIndex < deviceNumber; ++deviceIndex ) {
        if( devices[deviceIndex].use == deviceType ) {
            deviceId = devices[deviceIndex].deviceid;
            break;
        }
    }

    ::XIFreeDeviceInfo( devices );

    return deviceId;
}

InputX11* InputX11::getInstance() {
    const auto create = [] {
        Window window = RenderingWindowX11::getInstance()->getHandle();
        return new InputX11( getDisplayHandleX11(), window );
    };
    static const std::unique_ptr<InputX11> instance( create() );
    return instance.get();
}

}
