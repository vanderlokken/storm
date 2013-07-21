#include "MouseWin.h"

#include "Exception.h"
#include "InputWin.h"
#include "RenderingWindowWin.h"
#include "WindowProcedureWin.h"

// The following definitions were taken from MSDN
// See http://msdn.microsoft.com/en-us/library/ff543477%28v=VS.85%29.aspx

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif

namespace storm {

MouseWin::MouseWin()
    : _buttonPressed( ButtonCount, false ),
      _cursorVisible( true ),
      _cursorMovementRestricted( false ),
      _cursorLocked( false ),
      _originalWindowProcedure( nullptr )
{
    registerInputDevice( HID_USAGE_PAGE_GENERIC, HID_USAGE_GENERIC_MOUSE );

    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    _originalWindowProcedure = replaceWindowProcedure( windowHandle, &MouseWin::handleMessage );
    return;
}

MouseWin::~MouseWin() {
    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();
    replaceWindowProcedure( windowHandle, _originalWindowProcedure );
    return;
}

void MouseWin::addEventHandler( const EventHandler<ButtonPressEvent> &handler ) {
    _buttonPressEventHandlers.addEventHandler( handler );
    return;
}

void MouseWin::addEventHandler( const EventHandler<ButtonReleaseEvent> &handler ) {
    _buttonReleaseEventHandlers.addEventHandler( handler );
    return;
}

void MouseWin::addEventHandler( const EventHandler<WheelRotationEvent> &handler ) {
    _wheelRotationEventHandlers.addEventHandler( handler );
    return;
}

void MouseWin::addEventHandler( const EventHandler<MovementEvent> &handler ) {
    _movementEventHandlers.addEventHandler( handler );
    return;
}

bool MouseWin::isButtonPressed( Button button ) const noexcept {
    if( button <= ButtonCount )
        return _buttonPressed[button];
    else
        return false;
}

bool MouseWin::getCursorVisibility() const noexcept{
    return _cursorVisible;
}

void MouseWin::setCursorVisibility( bool visible ) noexcept {
    if( visible == _cursorVisible )
        return;

    // The following code forces the window manager to send WM_SETCURSOR

    POINT cursorPosition;
    ::GetCursorPos( &cursorPosition );

    ::SetCursorPos( cursorPosition.x, cursorPosition.y );

    _cursorVisible = visible;
    return;
}

bool MouseWin::getCursorMovementRestriction() const noexcept {
    return _cursorMovementRestricted;
}

void MouseWin::setCursorMovementRestriction( bool restricted ) noexcept {
    if( restricted == _cursorMovementRestricted )
        return;

    if( RenderingWindowWin::getInstance()->isActive() && isCursorInClientRectangle() )
        if( restricted )
            lockCursor();
        else
            unlockCursor();

    _cursorMovementRestricted = restricted;
    return;
}

void MouseWin::processMouseInputEvent( const RAWMOUSE &mouse ) {
    const USHORT state = mouse.usFlags;
    const USHORT stateChanges = mouse.usButtonFlags;

    if( isCursorLockRequired() )
        return;

    // Button release events

    if( stateChanges & RI_MOUSE_BUTTON_1_UP )
        processButtonRelease( ButtonLeft );

    if( stateChanges & RI_MOUSE_BUTTON_2_UP )
        processButtonRelease( ButtonRight );

    if( stateChanges & RI_MOUSE_BUTTON_3_UP )
        processButtonRelease( ButtonMiddle );

    if( stateChanges & RI_MOUSE_BUTTON_4_UP )
        processButtonRelease( ButtonSideFirst );

    if( stateChanges & RI_MOUSE_BUTTON_5_UP )
        processButtonRelease( ButtonSideSecond );

    // The further events are processed only when the cursor is inside
    // the client area of the rendering window and the rendering window is active

    if( !isCursorInClientRectangle() )
        return;

    if( !RenderingWindowWin::getInstance()->isActive() )
        return;

    // Button press events

    if( stateChanges & RI_MOUSE_BUTTON_1_DOWN )
        processButtonPress( ButtonLeft );

    if( stateChanges & RI_MOUSE_BUTTON_2_DOWN )
        processButtonPress( ButtonRight );

    if( stateChanges & RI_MOUSE_BUTTON_3_DOWN )
        processButtonPress( ButtonMiddle );

    if( stateChanges & RI_MOUSE_BUTTON_4_DOWN )
        processButtonPress( ButtonSideFirst );

    if( stateChanges & RI_MOUSE_BUTTON_5_DOWN )
        processButtonPress( ButtonSideSecond );

    // A wheel scroll event

    // For some reason RAWMOUSE::usButtonData contains a rotation distance

    if( stateChanges & RI_MOUSE_WHEEL )
        processWheelRotation( mouse.usButtonData );

    // A movement event

    if( !(state & MOUSE_MOVE_ABSOLUTE) )
        processMovement( mouse.lLastX, mouse.lLastY );

    if( state & MOUSE_MOVE_ABSOLUTE )
        throwRuntimeError( "Not implemented" );

    return;
}

void MouseWin::processButtonPress( Button button ) {
    _buttonPressed[button] = true;

    ButtonPressEvent event;
    event.button = button;
    _buttonPressEventHandlers( event );
    return;
}

void MouseWin::processButtonRelease( Button button ) {

    // There might be some situations when button release events shouldn't be received

    // For example a user can press some button while the rendering window is not
    // active and then activate the rendering window and release the pressed button

    if( !_buttonPressed[button] )
        return;

    _buttonPressed[button] = false;

    ButtonReleaseEvent event;
    event.button = button;
    _buttonReleaseEventHandlers( event );
    return;
}

void MouseWin::processWheelRotation( short distance ) {
    WheelRotationEvent event = { distance };
    _wheelRotationEventHandlers( event );
    return;
}

void MouseWin::processMovement( int x, int y ) {
    MovementEvent event = { x, y };
    _movementEventHandlers( event );
    return;
}

bool MouseWin::isCursorLockRequired() noexcept {
    return _cursorMovementRestricted && !_cursorLocked;
}

bool MouseWin::isCursorInClientRectangle() noexcept {
    POINT cursorPosition;

    ::GetCursorPos( &cursorPosition );

    auto instance = RenderingWindowWin::getInstance();

    const HWND windowHandle = instance->getHandle();
    const Dimensions windowDimensions = instance->getDimensions();

    ::ScreenToClient( windowHandle, &cursorPosition );

    return
        cursorPosition.x >= 0 &&
        cursorPosition.y >= 0 &&
        cursorPosition.x < windowDimensions.getWidth() &&
        cursorPosition.y < windowDimensions.getHeight();
}

void MouseWin::lockCursor() noexcept {
    const HWND windowHandle = RenderingWindowWin::getInstance()->getHandle();

    RECT rectangle;
    ::GetClientRect( windowHandle, &rectangle );

    POINT topLeftCorner = { rectangle.left, rectangle.top };
    ::ClientToScreen( windowHandle, &topLeftCorner );

    ::OffsetRect( &rectangle, topLeftCorner.x, topLeftCorner.y );

    ::ClipCursor( &rectangle );

    _cursorLocked = true;
    return;
}

void MouseWin::unlockCursor() noexcept {
    ::ClipCursor( nullptr );

    _cursorLocked = false;
    return;
}

const LRESULT USE_DEFAULT_PROCESSING = ~0U;

LRESULT CALLBACK MouseWin::handleMessage(
    HWND windowHandle, UINT message, WPARAM firstParameter, LPARAM secondParameter )
{
    auto mouse = MouseWin::getInstance();

    LRESULT result = USE_DEFAULT_PROCESSING;

    switch( message ) {
    case WM_INPUT:
        result = mouse->handleInputMessage( firstParameter, secondParameter );
        break;

    case WM_SETCURSOR:
        result = mouse->handleCursorMessage( firstParameter, secondParameter );
        break;

    case WM_ACTIVATEAPP:
        result = mouse->handleActivationMessage( firstParameter, secondParameter );
        break;

    case WM_LBUTTONDOWN:
        result = mouse->handleLeftButtonPressMessage( firstParameter, secondParameter );
        break;
    }

    if( result != USE_DEFAULT_PROCESSING )
        return result;

    return ::CallWindowProc( mouse->_originalWindowProcedure,
        windowHandle, message, firstParameter, secondParameter );
}

LRESULT MouseWin::handleInputMessage( WPARAM, LPARAM secondParameter ) {

    const HRAWINPUT inputHandle = reinterpret_cast< HRAWINPUT >( secondParameter );
    const RAWINPUT inputData = receiveInputData( inputHandle );

    if( inputData.header.dwType == RIM_TYPEMOUSE )
        processMouseInputEvent( inputData.data.mouse );

    return USE_DEFAULT_PROCESSING;
}

LRESULT MouseWin::handleCursorMessage( WPARAM, LPARAM secondParameter ) noexcept {

    // The following code makes the cursor invisible when it's required

    const WORD windowPart = LOWORD( secondParameter );

    if( windowPart != HTCLIENT )
        return USE_DEFAULT_PROCESSING;

    if( _cursorVisible )
        return USE_DEFAULT_PROCESSING;

    if( isCursorLockRequired() )
        return USE_DEFAULT_PROCESSING;

    if( !RenderingWindowWin::getInstance()->isActive() )
        return USE_DEFAULT_PROCESSING;

    ::SetCursor( nullptr );

    // Disable the following processing
    return TRUE;
}

LRESULT MouseWin::handleActivationMessage( WPARAM firstParameter, LPARAM ) noexcept {

    const BOOL activated = firstParameter;

    if( !activated ) {
        unlockCursor();

        processButtonRelease( ButtonLeft );
        processButtonRelease( ButtonRight );
        processButtonRelease( ButtonMiddle );
        processButtonRelease( ButtonSideFirst );
        processButtonRelease( ButtonSideSecond );
    }

    return USE_DEFAULT_PROCESSING;
}

LRESULT MouseWin::handleLeftButtonPressMessage( WPARAM, LPARAM ) noexcept {

    if( isCursorLockRequired() )
        lockCursor();

    return USE_DEFAULT_PROCESSING;
}

std::shared_ptr<MouseWin> MouseWin::getInstance() {
    static std::shared_ptr<MouseWin> instance( new MouseWin );
    return instance;
}

std::shared_ptr<Mouse> Mouse::getInstance() {
    return MouseWin::getInstance();
}

}