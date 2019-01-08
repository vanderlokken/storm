#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>

#include <storm/dimensions.h>
#include <storm/input.h>
#include <storm/vector.h>

namespace storm {

struct WindowObserver {
    std::function<void()> onShutdownRequested;

    std::function<void()> onFocusReceived;
    std::function<void()> onFocusLost;

    // This function is called when the window dimensions are changed.
    //
    // It allows to handle display resolution changes when the window is in
    // the windowed fullscreen mode.
    std::function<void()> onResized;

    std::function<void(IntVector2d)> onMouseMotion;
    std::function<void(MouseButton)> onMouseButtonPressed;
    std::function<void(MouseButton)> onMouseButtonReleased;
    std::function<void(float)> onMouseWheelRotated;

    // This function is called when a pointer moves over the window.
    // The argument stores client pointer coordinates in pixels.
    std::function<void(IntVector2d)> onPointerMotion;

    std::function<void(KeyboardKey)> onKeyboardKeyPressed;
    std::function<void(KeyboardKey)> onKeyboardKeyRepeated;
    std::function<void(KeyboardKey)> onKeyboardKeyReleased;

    std::function<void(char32_t)> onCharacterInput;
};

class Window {
public:
    using Pointer = std::shared_ptr<Window>;

    // A created window is invisible and set to the windowed fullscreen mode.
    static Pointer create();

    virtual ~Window() {}

    // This method can be called only from the thread where the window was
    // created.
    virtual void processEvents() = 0;

    // The observer is automatically removed when the 'observer.expired()'
    // condition is true.
    virtual void addObserver( std::weak_ptr<WindowObserver> observer ) = 0;

    virtual void* getHandle() const = 0;

    // Returns the dimensions of the client area in pixels.
    virtual Dimensions getDimensions() const = 0;

    virtual void setWindowedFullscreenMode() = 0;
    virtual void setWindowedMode( Dimensions dimensions ) = 0;

    virtual bool isVisible() const = 0;
    virtual void setVisible( bool visible ) = 0;

    virtual bool hasFocus() const = 0;

    virtual std::string_view getTitle() const = 0;
    // The 'title' should be a UTF-8 encoded value.
    virtual void setTitle( std::string title ) = 0;

    virtual bool isPointerVisible() const = 0;
    virtual void setPointerVisible( bool visible ) = 0;

    // When pointer locking is enabled, the pointer is confined within the
    // client area of the window. The confinement is applied only when the
    // window is active.
    virtual bool isPointerLocked() const = 0;
    virtual void setPointerLocked( bool locked ) = 0;

    // TODO: add the pointer icon control API
    // TODO: add the window icon control API
};

}
