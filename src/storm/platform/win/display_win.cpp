#include <storm/platform/win/display_win.h>

#include <memory>

namespace storm {

Display::Mode DisplayWin::getDefaultMode() const {
    const wchar_t *deviceName = nullptr;

    DEVMODE mode = {};
    mode.dmSize = sizeof( mode );

    ::EnumDisplaySettings(
        deviceName, ENUM_REGISTRY_SETTINGS, &mode );

    return convertMode( mode );
}

std::vector<Display::Mode> DisplayWin::getSupportedModes() const {
    std::vector<Mode> supportedModes;

    const wchar_t *deviceName = nullptr;

    DWORD modeIndex = 0;

    DEVMODE mode = {};
    mode.dmSize = sizeof( mode );

    while( ::EnumDisplaySettings(deviceName, modeIndex, &mode) ) {
        if( mode.dmBitsPerPel == 32 )
            supportedModes.push_back( convertMode(mode) );
        ++modeIndex;
    }
    return supportedModes;
}

Display::Mode DisplayWin::convertMode( const DEVMODE &mode ) {
    return {
        mode.dmPelsWidth,
        mode.dmPelsHeight,
        mode.dmDisplayFrequency
    };
}

Display* Display::getInstance() {
    static const std::unique_ptr<DisplayWin> instance( new DisplayWin );
    return instance.get();
}

}
