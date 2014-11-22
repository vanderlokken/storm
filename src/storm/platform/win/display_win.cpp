#include <storm/platform/win/display_win.h>

#include <memory>

#include <storm/platform/win/api_win.h>
#include <storm/throw_exception.h>

namespace storm {

DisplayWin::DisplayWin() {
    const wchar_t *deviceName = nullptr;

    DEVMODE mode = {};
    mode.dmSize = sizeof( mode );
    mode.dmDriverExtra = 0;

    ::EnumDisplaySettings(
        deviceName, ENUM_CURRENT_SETTINGS, &mode );

    _currentMode.width = mode.dmPelsWidth;
    _currentMode.height = mode.dmPelsHeight;
    _currentMode.refreshRate = mode.dmDisplayFrequency;
    _currentMode.colorDepth = mode.dmBitsPerPel;
}

std::vector<Display::Mode> DisplayWin::getSupportedModes() const {
    std::vector<Mode> supportedModes;

    const wchar_t *deviceName = nullptr;

    DWORD modeIndex = 0;

    DEVMODE mode;
    mode.dmSize = sizeof( mode );
    mode.dmDriverExtra = 0;

    while( ::EnumDisplaySettings(deviceName, modeIndex, &mode) ) {
        Mode supportedMode;

        supportedMode.width = mode.dmPelsWidth;
        supportedMode.height = mode.dmPelsHeight;
        supportedMode.refreshRate = mode.dmDisplayFrequency;
        supportedMode.colorDepth = mode.dmBitsPerPel;

        supportedModes.push_back( supportedMode );

        ++modeIndex;
    }
    return supportedModes;
}

const Display::Mode& DisplayWin::getCurrentMode() const {
    return _currentMode;
}

void DisplayWin::setCurrentMode( const Mode &mode ) {
    throwNotImplemented();
}

DisplayWin* DisplayWin::getInstance() {
    static const std::unique_ptr<DisplayWin> instance( new DisplayWin );
    return instance.get();
}

Display* Display::getInstance() {
    return DisplayWin::getInstance();
}

}
