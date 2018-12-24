#pragma once

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <storm/dimensions.h>
#include <storm/keyboard.h>
#include <storm/mouse.h>
#include <storm/vector.h>

namespace storm {

struct WindowObserver {
    std::function<void()> onShutdownRequested;

    std::function<void()> onFocusReceived;
    std::function<void()> onFocusLost;

    // This function is called when the window is in the windowed fullscreen
    // mode and the display resolution is changed.
    std::function<void()> onResized;

    std::function<void(IntVector2d)> onMouseMotion;
    std::function<void(Mouse::Button)> onMouseButtonPressed;
    std::function<void(Mouse::Button)> onMouseButtonReleased;
    std::function<void(float)> onMouseWheelRotated;

    std::function<void(IntVector2d)> onPointerMotion;

    std::function<void(Keyboard::Key)> onKeyboardKeyPressed;
    std::function<void(Keyboard::Key)> onKeyboardKeyRepeated;
    std::function<void(Keyboard::Key)> onKeyboardKeyReleased;
};

class Window {
public:
    using Pointer = std::shared_ptr<Window>;

    // A created window is invisible and set to the windowed fullscreen mode.
    static Pointer create();

    virtual ~Window() {}

    virtual void processEvents() = 0;

    virtual void setObserver( WindowObserver observer ) = 0;

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

class ProxyWindowObserver {
public:
    ProxyWindowObserver();

    ProxyWindowObserver( const ProxyWindowObserver& ) = delete;
    ProxyWindowObserver& operator = ( const ProxyWindowObserver& ) = delete;

    ProxyWindowObserver( ProxyWindowObserver&& ) = default;
    ProxyWindowObserver& operator = ( ProxyWindowObserver&& ) = default;

    operator WindowObserver() const;

    void addObserver( std::weak_ptr<WindowObserver> observer );

private:
    std::shared_ptr<std::vector<std::weak_ptr<WindowObserver>>> _observers;
};

}
