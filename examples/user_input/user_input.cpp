#include <clocale>
#include <cuchar>
#include <iostream>
#include <string>
#include <string_view>

#include <storm/window.h>

#include "../example_base.h"

const storm::Dimensions outputWindowDimensions( 640, 480 );

void outputString( std::string_view string ) {
#ifdef _WIN32
    OutputDebugStringA( string.data() );
    OutputDebugStringA( "\n" );
#endif
    std::setlocale( LC_ALL, "en_US.utf-8" );
    std::cout << string << std::endl;
}

class Example : public ExampleBase {
public:
    explicit Example( storm::Window::Pointer window ) :
        _window( std::move(window) ),
        _observer( std::make_shared<storm::WindowObserver>() )
    {
        _window->setWindowedMode( outputWindowDimensions );
        _window->addObserver( _observer );

        _observer->onShutdownRequested = [] {
            outputString( "Shutdown requested" );
        };
        _observer->onFocusReceived = [] {
            outputString( "Focus received" );
        };
        _observer->onFocusLost = [] {
            outputString( "Focus lost" );
        };
        _observer->onResized = [this] {
            outputString(
                "The window size is changed. The new size is: " +
                    std::to_string(_window->getDimensions().width) + ", " +
                    std::to_string(_window->getDimensions().height) );
        };
        _observer->onMouseMotion = []( storm::IntVector2d value ) {
            outputString(
                "The mouse is moved. The delta is: " +
                    std::to_string(value.x) + ", " +
                    std::to_string(value.y) );
        };
        _observer->onMouseButtonPressed = []( storm::MouseButton value ) {
            outputString(
                "The mouse button is pressed. The value is: " +
                    std::to_string(static_cast<int>(value)) );
        };
        _observer->onMouseButtonReleased = []( storm::MouseButton value ) {
            outputString(
                "The mouse button is released. The value is: " +
                    std::to_string(static_cast<int>(value)) );
        };
        _observer->onMouseWheelRotated = []( float value ) {
            outputString(
                "The mouse wheel is rotated. The delta is: " +
                    std::to_string(value) );
        };
        _observer->onPointerMotion = []( storm::IntVector2d value ) {
            outputString(
                "The mouse pointer is moved. The position is: " +
                    std::to_string(value.x) + ", " +
                    std::to_string(value.y) );
        };
        _observer->onKeyboardKeyPressed = [this]( storm::KeyboardKey value ) {
            outputString(
                "A keyboard key is pressed. The key is: " +
                    std::string(getKeyboardKeyName(value)) );

            processKeyPress( value );
        };
        _observer->onKeyboardKeyRepeated = []( storm::KeyboardKey value ) {
            outputString(
                "A keyboard key is repeated. The key is: " +
                    std::string(getKeyboardKeyName(value)) );
        };
        _observer->onKeyboardKeyReleased = []( storm::KeyboardKey value ) {
            outputString(
                "A keyboard key is released. The key is: " +
                    std::string(getKeyboardKeyName(value)) );
        };
        _observer->onCharacterInput = []( char32_t character ) {
            std::mbstate_t state = {};
            std::string buffer( MB_CUR_MAX, 0 );
            std::c32rtomb( buffer.data(), character, &state );

            outputString( "Character input: " + buffer +
                " (" + std::to_string(character) + ")" );
        };
    }

    void update() override {}
    void render() override {}

private:
    void processKeyPress( storm::KeyboardKey key ) {
        switch( key ){
        case storm::KeyboardKey::P:
            _window->setPointerVisible( !_window->isPointerVisible() );
            break;

        case storm::KeyboardKey::L:
            _window->setPointerLocked( !_window->isPointerLocked() );
            break;

        case storm::KeyboardKey::M:
            if( _isFullscreenMode ) {
                _window->setWindowedMode( outputWindowDimensions );
            } else {
                _window->setWindowedFullscreenMode();
            }
            _isFullscreenMode = !_isFullscreenMode;
            break;

        default:
            break;
        }
    }

    std::shared_ptr<storm::Window> _window;
    std::shared_ptr<storm::WindowObserver> _observer;

    bool _isFullscreenMode = false;
};

std::unique_ptr<ExampleBase> createExample( storm::Window::Pointer window ) {
    return std::make_unique<Example>( std::move(window) );
}
