#include "DisplayWin.h"

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include "Exception.h"

namespace storm {

DisplayWin::DisplayWin()
    : _currentMode( 0, 0, 0, 0 )
{
    const wchar_t *deviceName = nullptr;
    
    DEVMODE mode;
    mode.dmSize = sizeof( mode );
    mode.dmDriverExtra = 0;
    
    const BOOL result = ::EnumDisplaySettings( deviceName, ENUM_CURRENT_SETTINGS, &mode );
    if( !result ) {
        throwRuntimeError( "::EnumDisplaySettings has failed" );
    }
    
    _currentMode = Mode(
        mode.dmPelsWidth,
        mode.dmPelsHeight,
        mode.dmDisplayFrequency,
        mode.dmBitsPerPel );
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
        Mode supportedMode(
            mode.dmPelsWidth,
            mode.dmPelsHeight,
            mode.dmDisplayFrequency,
            mode.dmBitsPerPel );
        supportedModes.push_back( supportedMode );
        modeIndex++;
    }
    return supportedModes;
}

const Display::Mode& DisplayWin::getCurrentMode() const noexcept {
    return _currentMode;
}

void DisplayWin::setCurrentMode( const Mode &mode ) {
    throwRuntimeError( "Not implemented" );
}

std::shared_ptr<DisplayWin> DisplayWin::getInstance() {
    static std::shared_ptr<DisplayWin> instance( new DisplayWin );
    return instance;
}

std::shared_ptr<Display> Display::getInstance() {
    return DisplayWin::getInstance();
}

}