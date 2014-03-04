#include <storm/platform/win/display_win.h>

#include <memory>

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <storm/throw_exception.h>

namespace storm {

DisplayWin::DisplayWin() {
    const wchar_t *deviceName = nullptr;

    DEVMODE mode;
    mode.dmSize = sizeof( mode );
    mode.dmDriverExtra = 0;

    const BOOL result = ::EnumDisplaySettings(
        deviceName, ENUM_CURRENT_SETTINGS, &mode );
    if( !result ) {
        throwRuntimeError( "::EnumDisplaySettings has failed" );
    }

    _currentMode.width = mode.dmPelsWidth;
    _currentMode.height = mode.dmPelsHeight;
    _currentMode.refreshRate = mode.dmDisplayFrequency;
    _currentMode.colorDepth = mode.dmBitsPerPel;
    return;
}

std::vector<Display::Mode> DisplayWin::getSupportedModes() const noexcept {
    std::vector< Mode > supportedModes;

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

const Display::Mode& DisplayWin::getCurrentMode() const noexcept {
    return _currentMode;
}

void DisplayWin::setCurrentMode( const Mode &mode ) {
    throwRuntimeError( "Not implemented" );
}

DisplayWin* DisplayWin::getInstance() {
    static const std::unique_ptr<DisplayWin> instance( new DisplayWin );
    return instance.get();
}

Display* Display::getInstance() {
    return DisplayWin::getInstance();
}

}
