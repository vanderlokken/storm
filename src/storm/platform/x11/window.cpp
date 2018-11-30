#include <storm/window.h>

namespace {

class WindowImplementation : public Window {
public:
    WindowImplementation() {
    }

private:
};

} // namespace

std::unique_ptr<Window> Window::create() {
    return std::make_unique<WindowImplementation>();
}
