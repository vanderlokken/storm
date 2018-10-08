#pragma once

#include <memory>
#include <optional>
#include <string>
#include <variant>

namespace storm::window_events {

struct ShutdownRequested {};

// Alt+Enter handling
struct FullscreenModeRequested {};
struct WindowedModeRequested {};

// Mouse events
struct MouseButtonPressed {
    MouseButton button;
};
struct MouseButtonReleased {
    MouseButton button;
};
struct MouseWheelRotated {
    MouseButton button;
};
struct MouseMoved {
    IntVector2d displacement;
};
struct MouseCursorMoved {
    IntVector2d position;
    IntVector2d displacement;
};

} // namespace storm::window_events

namespace storm {

// Observer?
using WindowEvent = std::variant<
    ShutdownRequested,
    FullscreenModeRequested,
    WindowedModeRequested,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseWheelRotated,
    MouseMoved,
    MouseCursorMoved
>;

class Window {
public:
    std::unique_ptr<Window> create();

    virtual ~Window() {}

    // ?
    virtual std::optional<WindowEvent> getEvent() = 0;
    virtual WindowEvent waitEvent() = 0;

    // ?
    virtual Dimensions getDimensions() const = 0;
    virtual void setWindowed( Dimensions dimensions ) = 0;
    virtual void setWindowedFullscreen() = 0;

    virtual bool isVisible() const = 0;
    virtual void setVisible( bool visible ) = 0;

    virtual std::string_view getTitle() const = 0;
    // Throws an exception if 'title' is not a valid UTF-8 encoded value.
    virtual void setTitle( std::string title ) = 0;

    virtual bool isMouseCursorVisible() const = 0;
    virtual void setMouseCursorVisible( bool visible ) = 0;

    // ?
    virtual bool isMouseCursorLocked() const = 0;
    virtual void setMouseCursorLocked( bool locked ) = 0;
};

}
