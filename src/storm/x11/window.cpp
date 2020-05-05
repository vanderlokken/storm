#include <storm/window.h>

#include <array>
#include <climits>
#include <optional>
#include <unordered_map>

#include <xcb/xcb.h>
#include <xcb/xfixes.h>
#include <xcb/xinput.h>

#include <storm/exception.h>
#include <storm/x11/invisible_cursor.h>
#include <storm/x11/keyboard_state_xkb.h>
#include <storm/x11/pointer_locking_region.h>
#include <storm/x11/xcb_connection.h>
#include <storm/x11/xcb_pointer.h>
#include <storm/proxy_window_observer.h>

namespace storm {

namespace {

template <class T, class... Args>
void runCallback( const std::function<T> &callback, Args&&... args ) {
    if( callback ) {
        callback( std::forward<Args>(args)... );
    }
}

Rectangle getWindowRectangle(
    xcb_connection_t *connection, xcb_window_t window )
{
    const xcb_get_geometry_cookie_t request =
        xcb_get_geometry_unchecked( connection, window );

    const xcb_get_geometry_reply_t *reply =
        xcb_get_geometry_reply( connection, request, nullptr );

    if( reply ) {
        return {
            reply->x,
            reply->y,
            reply->width,
            reply->height
        };
    }

    return {};
}

Dimensions getWindowDimensions(
    xcb_connection_t *connection, xcb_window_t window )
{
    const Rectangle rectangle = getWindowRectangle( connection, window );
    return {rectangle.width, rectangle.height};
}

class WindowImplementation : public Window {
public:
    WindowImplementation() :
        _connection( XcbConnection::create() ),
        _invisibleCursor( _connection, _connection.getDefaultScreen() ),
        _handle( xcb_generate_id(_connection) ),
        _wmDeleteWindow( _connection.getAtom("WM_DELETE_WINDOW") ),
        _dimensions(
            getWindowDimensions(
                _connection, _connection.getDefaultScreen()->root) )
    {
        _eventHandlers = {
            {XCB_INPUT_BUTTON_PRESS, &WindowImplementation::onButtonPress},
            {XCB_INPUT_BUTTON_RELEASE, &WindowImplementation::onButtonRelease},
            {XCB_INPUT_FOCUS_IN, &WindowImplementation::onFocusIn},
            {XCB_INPUT_FOCUS_OUT, &WindowImplementation::onFocusOut},
            {XCB_INPUT_KEY_PRESS, &WindowImplementation::onKeyPress},
            {XCB_INPUT_KEY_RELEASE, &WindowImplementation::onKeyRelease},
            {XCB_INPUT_MOTION, &WindowImplementation::onMotion},
            {XCB_INPUT_RAW_MOTION, &WindowImplementation::onRawMotion}
        };

        queryRequiredExtensions();

        _keyboardState = std::make_unique<KeyboardStateXkb>( _connection );

        const uint32_t attributeMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        const uint32_t attributes[] = {
            _connection.getDefaultScreen()->black_pixel,
            XCB_EVENT_MASK_STRUCTURE_NOTIFY
        };

        xcb_create_window(
            _connection,
            XCB_COPY_FROM_PARENT,
            _handle,
            _connection.getDefaultScreen()->root,
            0,
            0,
            _dimensions.width,
            _dimensions.height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            _connection.getDefaultScreen()->root_visual,
            attributeMask,
            attributes );

        selectXinputEvents(
            _handle,
            (
                XCB_INPUT_XI_EVENT_MASK_BUTTON_PRESS |
                XCB_INPUT_XI_EVENT_MASK_BUTTON_RELEASE |
                XCB_INPUT_XI_EVENT_MASK_FOCUS_IN |
                XCB_INPUT_XI_EVENT_MASK_FOCUS_OUT |
                XCB_INPUT_XI_EVENT_MASK_KEY_PRESS |
                XCB_INPUT_XI_EVENT_MASK_KEY_RELEASE |
                XCB_INPUT_XI_EVENT_MASK_MOTION
            ));

        selectXinputEvents(
            _connection.getDefaultScreen()->root,
            (
                XCB_INPUT_XI_EVENT_MASK_RAW_MOTION
            ));

        enableShutdownEvent();
        removeDecorations();
        setWindowedFullscreenMode();
    }

    ~WindowImplementation() {
        xcb_destroy_window( _connection, _handle );
    }

    void processEvents() override {
        xcb_flush( _connection );

        while(
            const XcbPointer<xcb_generic_event_t> genericEvent =
                xcb_poll_for_event(_connection) )
        {
            const uint8_t eventType = genericEvent->response_type & ~0x80;

            if( eventType == XCB_GE_GENERIC ) {
                const auto &event = reinterpret_cast<
                    const xcb_ge_generic_event_t&>( *genericEvent );

                if( event.extension == _xinputOpcode ) {
                    const auto iterator =
                        _eventHandlers.find( event.event_type );

                    if( iterator != _eventHandlers.end() ) {
                        const auto handler = iterator->second;
                        (this->*handler)( &event );
                    }
                }
            }

            if( eventType == XCB_CONFIGURE_NOTIFY ) {
                const auto &event = reinterpret_cast<
                    const xcb_configure_notify_event_t&>( *genericEvent );

                updateDimensions( Dimensions(event.width, event.height) );
                updatePointerLockingRegion();
            }

            if( eventType == XCB_CLIENT_MESSAGE ) {
                const auto &event = reinterpret_cast<
                    const xcb_client_message_event_t&>( *genericEvent );

                if( event.window == _handle &&
                    event.data.data32[0] == _wmDeleteWindow )
                {
                    runCallback( _proxyObserver->onShutdownRequested );
                }
            }

            if( eventType == _xkbEvent ) {
                struct AnyXkbEvent {
                    uint8_t responseType;
                    uint8_t xkbType;
                };

                const auto &event =
                    reinterpret_cast<const AnyXkbEvent&>( *genericEvent );

                if( event.xkbType == XCB_XKB_STATE_NOTIFY ) {
                    _keyboardState->update(
                        reinterpret_cast<const xcb_xkb_state_notify_event_t&>(
                            *genericEvent) );
                }
            }

#ifndef NDEBUG
            if( eventType == 0 ) {
                const auto &error = reinterpret_cast<
                    const xcb_generic_error_t&>( *genericEvent );

                throw Exception() << "XCB error (sequence = " <<
                    std::to_string( error.sequence ) << ")";
#endif
            }
        }
    }

    void addObserver( std::weak_ptr<WindowObserver> observer ) override {
        _proxyObserver.addObserver( std::move(observer) );
    }

    void* getHandle() const override {
        return reinterpret_cast<void*>( _handle );
    }

    Dimensions getDimensions() const override {
        return _dimensions;
    }

    void setWindowedFullscreenMode() override {
        setFullscreenModeEnabled( true );

        const Dimensions dimensions = getWindowDimensions(
            _connection, _connection.getDefaultScreen()->root );

        placeCentered( dimensions );
        updateDimensions( dimensions );
    }

    void setWindowedMode( Dimensions dimensions ) override {
        setFullscreenModeEnabled( false );

        placeCentered( dimensions );
        updateDimensions( dimensions );
    }

    bool isVisible() const override {
        const xcb_get_window_attributes_cookie_t request =
            xcb_get_window_attributes( _connection, _handle );

        const xcb_get_window_attributes_reply_t *reply =
            xcb_get_window_attributes_reply( _connection, request, nullptr );

        return reply && reply->map_state == XCB_MAP_STATE_VIEWABLE;
    }

    void setVisible( bool visible ) override {
        if( visible ) {
            xcb_map_window( _connection, _handle );

            // Some window managers change the position of a window only when
            // it's visible.
            placeCentered( _dimensions );
        } else {
            xcb_unmap_window( _connection, _handle );
        }
    }

    bool hasFocus() const override {
        const XcbPointer<xcb_get_input_focus_reply_t> reply =
            xcb_get_input_focus_reply(
                _connection, xcb_get_input_focus(_connection), nullptr );

        return reply && reply->focus == _handle;
    }

    std::string_view getTitle() const override {
        return _title;
    }

    void setTitle( std::string title ) override {
        _title = std::move( title );

        xcb_change_property(
            _connection,
            XCB_PROP_MODE_REPLACE,
            _handle,
            _connection.getAtom("_NET_WM_NAME"),
            _connection.getAtom("UTF8_STRING"),
            CHAR_BIT,
            _title.size(),
            _title.data() );
    }

    bool isPointerVisible() const override {
        return _isPointerVisible;
    }

    void setPointerVisible( bool visible ) override {
        _isPointerVisible = visible;

        const xcb_cursor_t cursor =
            _isPointerVisible ? XCB_CURSOR_NONE : _invisibleCursor.getHandle();

        xcb_change_window_attributes(
            _connection, _handle, XCB_CW_CURSOR, &cursor );
    }

    bool isPointerLocked() const override {
        return _isPointerLocked;
    }

    void setPointerLocked( bool locked ) override {
        _isPointerLocked = locked;

        updatePointerLockingRegion();
    }

private:
    void queryRequiredExtensions() {
        const char *missingXinputMessage =
            "The display server doesn't support version 2.0 of the "
            "'XInput' extension";
        const char *missingXfixesMessage =
            "The display server doesn't support version 5.0 of the "
            "'XFixes' extension";
        const char *missingXkbMessage =
            "The display server doesn't support version 1.0 of the "
            "'XKB' extension";

        const xcb_query_extension_reply_t *xinputExtension =
            xcb_get_extension_data( _connection, &xcb_input_id );
        const xcb_query_extension_reply_t *xfixesExtension =
            xcb_get_extension_data( _connection, &xcb_xfixes_id );

        if( !xinputExtension->present ) {
            throw SystemRequirementsNotMet() << missingXinputMessage;
        }
        if( !xfixesExtension->present ) {
            throw SystemRequirementsNotMet() << missingXfixesMessage;
        }

        _xinputOpcode = xinputExtension->major_opcode;

        const uint16_t requiredXinputVersion = 2;
        const uint16_t requiredXfixesVersion = 5;
        const uint16_t requiredXkbVersion = 1;

        const XcbPointer<xcb_input_xi_query_version_reply_t> xinputReply =
            xcb_input_xi_query_version_reply(
                _connection,
                xcb_input_xi_query_version_unchecked(
                    _connection, requiredXinputVersion, 0),
                nullptr );

        const XcbPointer<xcb_xfixes_query_version_reply_t> xfixesReply =
            xcb_xfixes_query_version_reply(
                _connection,
                xcb_xfixes_query_version_unchecked(
                    _connection, requiredXfixesVersion, 0),
                nullptr );

        if( !xinputReply ||
                xinputReply->major_version < requiredXinputVersion ) {
            throw SystemRequirementsNotMet() << missingXinputMessage;
        }
        if( !xfixesReply ||
                xfixesReply->major_version < requiredXfixesVersion ) {
            throw SystemRequirementsNotMet() << missingXfixesMessage;
        }


        if( !xkb_x11_setup_xkb_extension(
                _connection,
                requiredXkbVersion,
                0,
                XKB_X11_SETUP_XKB_EXTENSION_NO_FLAGS,
                nullptr,
                nullptr,
                &_xkbEvent,
                nullptr) ) {
            throw SystemRequirementsNotMet() << missingXkbMessage;
        }
    }

    void enableShutdownEvent() const {
        const std::array<xcb_atom_t, 1> protocols = { _wmDeleteWindow };

        xcb_change_property(
            _connection,
            XCB_PROP_MODE_REPLACE,
            _handle,
            _connection.getAtom("WM_PROTOCOLS"),
            XCB_ATOM_ATOM,
            sizeof(xcb_atom_t) * CHAR_BIT, // format, bits
            protocols.size(),
            protocols.data() );
    }

    void removeDecorations() const {
        const xcb_atom_t atom = _connection.getAtom( "_MOTIF_WM_HINTS" );

        // Note: see the 'Xm/MwmUtil.h' header file from the 'libmotif-dev'
        // package
        const std::array<uint32_t, 5> hints = { 2, 0, 0, 0, 0 };

        xcb_change_property(
            _connection,
            XCB_PROP_MODE_REPLACE,
            _handle,
            atom,
            atom,
            sizeof(uint32_t) * CHAR_BIT, // format, bits
            hints.size(),
            hints.data() );
    }

    void setFullscreenModeEnabled( bool enabled ) const {
        xcb_client_message_event_t event = {};

        event.response_type = XCB_CLIENT_MESSAGE;
        event.window = _handle;
        event.type = _connection.getAtom( "_NET_WM_STATE" );
        event.format = 32;
        event.data.data32[0] = enabled ? 1 : 0;
        event.data.data32[1] =
            _connection.getAtom( "_NET_WM_STATE_FULLSCREEN" );
        event.data.data32[2] = XCB_ATOM_NONE;
        event.data.data32[3] = 1; // source indication, that means "normal app."
        event.data.data32[4] = 0;

        xcb_send_event(
            _connection,
            0, // propagate
            _connection.getDefaultScreen()->root,
            XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
            XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY,
            reinterpret_cast<const char*>(&event) );
    }

    void selectXinputEvents( xcb_window_t window, uint32_t mask ) const {
        constexpr size_t bufferSize =
            sizeof( xcb_input_event_mask_t ) + sizeof( mask );

        std::array<unsigned char, bufferSize> buffer;

        xcb_input_event_mask_t *eventMask =
            reinterpret_cast<xcb_input_event_mask_t*>( buffer.data() );
        eventMask->deviceid = XCB_INPUT_DEVICE_ALL_MASTER;
        eventMask->mask_len = 1;

        *xcb_input_event_mask_mask( eventMask ) = mask;
        xcb_input_xi_select_events( _connection, window, 1, eventMask );
    }

    void onButtonPress( const xcb_ge_generic_event_t *genericEvent ) {
        onButtonStateChanged( genericEvent, /* pressed */ true );
    }

    void onButtonRelease( const xcb_ge_generic_event_t *genericEvent ) {
        onButtonStateChanged( genericEvent, /* pressed */ false );
    }

    void onFocusIn( const xcb_ge_generic_event_t* ) {
        runCallback( _proxyObserver->onFocusReceived );

        updatePointerLockingRegion();
    }

    void onFocusOut( const xcb_ge_generic_event_t* ) {
        runCallback( _proxyObserver->onFocusLost );

        _pointerLockingRegion.reset();
    }

    void onKeyPress( const xcb_ge_generic_event_t *genericEvent ) {
        onKeyStateChanged( genericEvent, /* pressed */ true );
    }

    void onKeyRelease( const xcb_ge_generic_event_t *genericEvent ) {
        onKeyStateChanged( genericEvent, /* pressed */ false );
    }

    void onMotion( const xcb_ge_generic_event_t *genericEvent ) {
        const auto *event = reinterpret_cast<
            const xcb_input_motion_event_t*>( genericEvent );

        // The following condition allows to distinguish between mouse motion
        // events and mouse wheel rotation events.
        const bool isMouseMotion =
            xcb_input_button_press_valuator_mask_length( event ) > 0 &&
            (*xcb_input_button_press_valuator_mask(event) & 0b11) == 0b11;

        if( isMouseMotion ) {
            runCallback(
                _proxyObserver->onPointerMotion,
                IntVector2d(
                    event->event_x >> 16,
                    event->event_y >> 16) );
        }
    }

    void onRawMotion( const xcb_ge_generic_event_t *genericEvent ) {
        const auto *event = reinterpret_cast<
            const xcb_input_raw_motion_event_t*>( genericEvent );

        const bool isMouseMotion =
            xcb_input_raw_button_press_valuator_mask_length( event ) > 0 &&
            (*xcb_input_raw_button_press_valuator_mask(event) & 0b11) == 0b11;

        if( hasFocus() && isMouseMotion ) {
            IntVector2d delta;

            xcb_input_fp3232_iterator_t iterator =
                xcb_input_raw_button_press_axisvalues_raw_iterator( event );

            delta.x = iterator.data->integral;

            xcb_input_fp3232_next( &iterator );

            delta.y = iterator.data->integral;

            runCallback( _proxyObserver->onMouseMotion, delta );
        }
    }

    void onButtonStateChanged(
        const xcb_ge_generic_event_t *genericEvent, bool pressed )
    {
        const auto *event = reinterpret_cast<
            const xcb_input_button_press_event_t*>( genericEvent );

        const std::array<std::optional<MouseButton>, 10> buttons = {
            std::nullopt,
            MouseButton::Left,
            MouseButton::Middle,
            MouseButton::Right,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            MouseButton::SideFirst,
            MouseButton::SideSecond
        };

        const size_t buttonIndex = event->detail;

        if( buttonIndex < buttons.size() && buttons[buttonIndex] ) {
            const MouseButton button = *buttons[buttonIndex];

            if( pressed ) {
                runCallback( _proxyObserver->onMouseButtonPressed, button );
            } else {
                runCallback( _proxyObserver->onMouseButtonReleased, button );
            }
        } else if( pressed ) {
            if( buttonIndex == 4 ) {
                runCallback( _proxyObserver->onMouseWheelRotated, 1.0 );
            }
            if( buttonIndex == 5 ) {
                runCallback( _proxyObserver->onMouseWheelRotated, -1.0 );
            }
        }
    }

    void onKeyStateChanged(
        const xcb_ge_generic_event_t *genericEvent, bool pressed )
    {
        const auto *event = reinterpret_cast<
            const xcb_input_key_press_event_t*>( genericEvent );

        const xcb_keycode_t keycode = event->detail;

        if( const std::optional<KeyboardKey> key =
                _keyboardState->getKey(keycode) ) {
            if( pressed ) {
                if( event->flags & XCB_INPUT_KEY_EVENT_FLAGS_KEY_REPEAT ) {
                    runCallback(
                        _proxyObserver->onKeyboardKeyRepeated, *key );
                } else {
                    runCallback(
                        _proxyObserver->onKeyboardKeyPressed, *key );
                }
            } else {
                runCallback( _proxyObserver->onKeyboardKeyReleased, *key );
            }
        }

        if( pressed ) {
            if( const std::optional<char32_t> character =
                    _keyboardState->getCharacter(keycode) ) {
                runCallback( _proxyObserver->onCharacterInput, *character );
            }
        }
    }

    void placeCentered( Dimensions windowDimensions ) const {
        const Dimensions screenDimensions = getWindowDimensions(
            _connection, _connection.getDefaultScreen()->root );

        const std::array<int32_t, 4> values = {
            (
                static_cast<int32_t>(screenDimensions.width) -
                static_cast<int32_t>(windowDimensions.width)
            ) / 2,
            (
                static_cast<int32_t>(screenDimensions.height) -
                static_cast<int32_t>(windowDimensions.height)
            ) / 2,
            static_cast<int32_t>(windowDimensions.width),
            static_cast<int32_t>(windowDimensions.height)
        };

        xcb_configure_window(
            _connection,
            _handle,
            XCB_CONFIG_WINDOW_X |
            XCB_CONFIG_WINDOW_Y |
            XCB_CONFIG_WINDOW_WIDTH |
            XCB_CONFIG_WINDOW_HEIGHT,
            values.data() );
    }

    void updateDimensions( Dimensions dimensions ) {
        if( dimensions.width != _dimensions.width ||
            dimensions.height != _dimensions.height )
        {
            _dimensions = dimensions;
            runCallback( _proxyObserver->onResized );
        }
    }

    void updatePointerLockingRegion() {
        if( !hasFocus() ) {
            return;
        }

        if( !_isPointerLocked ) {
            _pointerLockingRegion.reset();
        } else {
            _pointerLockingRegion.emplace(
                _connection,
                _handle,
                getWindowRectangle(_connection, _handle) );

            // TODO: do not move the pointer when it's already inside the
            // window.
            xcb_warp_pointer(
                _connection, XCB_WINDOW_NONE, _handle, 0, 0, 0, 0, 0, 0 );
        }
    }

    using EventHandler =
        void (WindowImplementation::*)( const xcb_ge_generic_event_t* );
    std::unordered_map<int, EventHandler> _eventHandlers;

    XcbConnection _connection;
    InvisibleCursor _invisibleCursor;

    xcb_window_t _handle = XCB_WINDOW_NONE;
    xcb_atom_t _wmDeleteWindow = XCB_ATOM_NONE;

    uint8_t _xinputOpcode = 0;
    uint8_t _xkbEvent = 0xff;

    ProxyWindowObserver _proxyObserver;

    std::string _title;
    Dimensions _dimensions;

    std::unique_ptr<KeyboardStateXkb> _keyboardState;

    bool _isPointerVisible = true;
    bool _isPointerLocked = false;

    std::optional<PointerLockingRegion> _pointerLockingRegion;
};

} // namespace

Window::Pointer Window::create() {
    return std::make_shared<WindowImplementation>();
}

}
