#include <storm/platform/win/mouse_win.h>

#include <memory>

#include <windowsx.h>

#include <storm/platform/win/input_win.h>
#include <storm/platform/win/rendering_window_win.h>
#include <storm/platform/win/window_procedure_win.h>

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

void MouseWin::addObserver( const Observer *observer ) {
    _observers.add( observer );
}

void MouseWin::removeObserver( const Observer *observer ) {
    _observers.remove( observer );
}

bool MouseWin::isButtonPressed( Button button ) const {
    const size_t buttonIndex = static_cast<size_t>( button );
    if( buttonIndex <= ButtonCount )
        return _buttonPressed[buttonIndex];
    else
        return false;
}

bool MouseWin::getCursorVisibility() const{
    return _cursorVisible;
}

void MouseWin::setCursorVisibility( bool visible ) {
    if( visible == _cursorVisible )
        return;

    // The following code forces the window manager to send WM_SETCURSOR

    POINT cursorPosition;
    ::GetCursorPos( &cursorPosition );

    ::SetCursorPos( cursorPosition.x, cursorPosition.y );

    _cursorVisible = visible;
    return;
}

bool MouseWin::getCursorMovementRestriction() const {
    return _cursorMovementRestricted;
}

void MouseWin::setCursorMovementRestriction( bool restricted ) {
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

Mouse::CursorPosition MouseWin::getCursorPosition() const {
    POINT point = {};
    ::GetCursorPos( &point );
    ::ScreenToClient( RenderingWindowWin::getInstance()->getHandle(), &point );
    return { point.x, point.y };
}

void MouseWin::processMouseInputEvent( const RAWMOUSE &mouse ) {
    const USHORT stateChanges = mouse.usButtonFlags;

    if( isCursorLockRequired() )
        return;

    // Button release events

    if( stateChanges & RI_MOUSE_BUTTON_1_UP )
        processButtonRelease( Button::Left );

    if( stateChanges & RI_MOUSE_BUTTON_2_UP )
        processButtonRelease( Button::Right );

    if( stateChanges & RI_MOUSE_BUTTON_3_UP )
        processButtonRelease( Button::Middle );

    if( stateChanges & RI_MOUSE_BUTTON_4_UP )
        processButtonRelease( Button::SideFirst );

    if( stateChanges & RI_MOUSE_BUTTON_5_UP )
        processButtonRelease( Button::SideSecond );

    // The further events are processed only when the cursor is inside
    // the client area of the rendering window and the rendering window is active

    if( !isCursorInClientRectangle() )
        return;

    if( !RenderingWindowWin::getInstance()->isActive() )
        return;

    // Button press events

    if( stateChanges & RI_MOUSE_BUTTON_1_DOWN )
        processButtonPress( Button::Left );

    if( stateChanges & RI_MOUSE_BUTTON_2_DOWN )
        processButtonPress( Button::Right );

    if( stateChanges & RI_MOUSE_BUTTON_3_DOWN )
        processButtonPress( Button::Middle );

    if( stateChanges & RI_MOUSE_BUTTON_4_DOWN )
        processButtonPress( Button::SideFirst );

    if( stateChanges & RI_MOUSE_BUTTON_5_DOWN )
        processButtonPress( Button::SideSecond );

    // A wheel scroll event

    // For some reason RAWMOUSE::usButtonData contains a rotation distance

    if( stateChanges & RI_MOUSE_WHEEL )
        processWheelRotation( mouse.usButtonData );

    // A movement event

    if( !(mouse.usFlags & MOUSE_MOVE_ABSOLUTE) && (mouse.lLastX || mouse.lLastY) )
        processMovement( {mouse.lLastX, mouse.lLastY} );
}

void MouseWin::processButtonPress( Button button ) {
    const size_t buttonIndex = static_cast<size_t>( button );
    _buttonPressed[buttonIndex] = true;

    _observers.notify( &Observer::onButtonPress, button );
}

void MouseWin::processButtonRelease( Button button ) {

    // There might be some situations when button release events shouldn't be received

    // For example a user can press some button while the rendering window is not
    // active and then activate the rendering window and release the pressed button

    const size_t buttonIndex = static_cast<size_t>( button );

    if( !_buttonPressed[buttonIndex] )
        return;

    _buttonPressed[buttonIndex] = false;

    _observers.notify( &Observer::onButtonRelease, button );
}

void MouseWin::processWheelRotation( short distance ) {
    _observers.notify( &Observer::onWheelRotation, distance );
}

void MouseWin::processMovement( Movement movement ) {
    _observers.notify( &Observer::onMovement, movement );
}

void MouseWin::processCursorMovement( CursorPosition cursorPosition ) {
    POINT point = { cursorPosition.x, cursorPosition.y };
    ::ClientToScreen(
        RenderingWindowWin::getInstance()->getHandle(), &point );

    MOUSEMOVEPOINT currentPosition = { point.x, point.y };
    MOUSEMOVEPOINT previousPositions[2] = { currentPosition, currentPosition };

    const int pointsToRetrieve = 2;
    const DWORD resolution = GMMP_USE_DISPLAY_POINTS;

    ::GetMouseMovePointsEx( sizeof(MOUSEMOVEPOINT),
        &currentPosition, previousPositions, pointsToRetrieve, resolution );

    const Movement movement = {
        currentPosition.x - previousPositions[1].x,
        currentPosition.y - previousPositions[1].y
    };

    _observers.notify( &Observer::onCursorMovement, movement, cursorPosition );
}

bool MouseWin::isCursorLockRequired() {
    return _cursorMovementRestricted && !_cursorLocked;
}

bool MouseWin::isCursorInClientRectangle() {
    POINT cursorPosition;

    ::GetCursorPos( &cursorPosition );

    auto instance = RenderingWindowWin::getInstance();

    const HWND windowHandle = instance->getHandle();
    const Dimensions windowDimensions = instance->getDimensions();

    ::ScreenToClient( windowHandle, &cursorPosition );

    return (
        cursorPosition.x >= 0 &&
        cursorPosition.y >= 0 &&
        static_cast<unsigned int>(cursorPosition.x) < windowDimensions.width &&
        static_cast<unsigned int>(cursorPosition.y) < windowDimensions.height
    );
}

void MouseWin::lockCursor() {
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

void MouseWin::unlockCursor() {
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

    case WM_MOUSEMOVE:
        result = mouse->handleCursorMovementMessage( firstParameter, secondParameter );
        break;

    case WM_SYSCOMMAND:
        result = mouse->handleSystemCommandMessage( firstParameter, secondParameter );
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

LRESULT MouseWin::handleCursorMessage( WPARAM, LPARAM secondParameter ) {

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

LRESULT MouseWin::handleActivationMessage( WPARAM firstParameter, LPARAM ) {

    const BOOL activated = firstParameter;

    if( !activated ) {
        unlockCursor();

        processButtonRelease( Button::Left );
        processButtonRelease( Button::Right );
        processButtonRelease( Button::Middle );
        processButtonRelease( Button::SideFirst );
        processButtonRelease( Button::SideSecond );
    }

    return USE_DEFAULT_PROCESSING;
}

LRESULT MouseWin::handleLeftButtonPressMessage( WPARAM, LPARAM ) {

    if( isCursorLockRequired() )
        lockCursor();

    return USE_DEFAULT_PROCESSING;
}

LRESULT MouseWin::handleCursorMovementMessage( WPARAM, LPARAM secondParameter ) {
    if( !isCursorLockRequired() ) {
        const CursorPosition cursorPosition = {
            GET_X_LPARAM(secondParameter),
            GET_Y_LPARAM(secondParameter)
        };
        processCursorMovement( cursorPosition );
    }

    return USE_DEFAULT_PROCESSING;
}

LRESULT MouseWin::handleSystemCommandMessage( WPARAM firstParameter, LPARAM ) {
    // By default pressing the Alt or F10 key causes the WM_ACTIVATEAPP message
    // to be sent with the HTCAPTION parameter which is undesired.
    if( firstParameter == SC_KEYMENU )
        return 0;

    return USE_DEFAULT_PROCESSING;
}

MouseWin* MouseWin::getInstance() {
    static const std::unique_ptr<MouseWin> instance( new MouseWin );
    return instance.get();
}

Mouse* Mouse::getInstance() {
    return MouseWin::getInstance();
}

}
