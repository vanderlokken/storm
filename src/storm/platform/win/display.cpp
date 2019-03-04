#include <storm/display.h>
#include <storm/platform/win/api_win.h>

#include <algorithm>
#include <memory>
#include <tuple>

namespace storm {

namespace {

std::tuple<unsigned int, unsigned int, unsigned int> toTuple(
    const Display::Mode &mode )
{
    return std::make_tuple(
        mode.width,
        mode.height,
        mode.refreshRate );
}

class DisplayImplementation : public Display {
public:
    Mode getDefaultMode() const override {
        const wchar_t *deviceName = nullptr;

        DEVMODE mode = {};
        mode.dmSize = sizeof( mode );

        EnumDisplaySettings(
            deviceName, ENUM_REGISTRY_SETTINGS, &mode );

        return convertMode( mode );
    }

    std::vector<Mode> getSupportedModes() const override {
        std::vector<Mode> supportedModes;

        const wchar_t *deviceName = nullptr;

        DWORD modeIndex = 0;

        DEVMODE mode = {};
        mode.dmSize = sizeof( mode );

        while( EnumDisplaySettings(deviceName, modeIndex, &mode) ) {
            if( mode.dmBitsPerPel == 32 ) {
                supportedModes.push_back( convertMode(mode) );
            }
            ++modeIndex;
        }

        std::sort(
            supportedModes.begin(),
            supportedModes.end(),
            [](const Mode& first, const Mode& second) {
                return toTuple( first ) < toTuple( second );
            });

        supportedModes.erase(
            std::unique(
                supportedModes.begin(),
                supportedModes.end(),
                [](const Mode& first, const Mode& second) {
                    return toTuple( first ) == toTuple( second );
                }),
            supportedModes.end() );

        return supportedModes;
    }

private:
    static Mode convertMode( const DEVMODE &mode ) {
        return {
            mode.dmPelsWidth,
            mode.dmPelsHeight,
            mode.dmDisplayFrequency
        };
    }
};

} // namespace

std::unique_ptr<Display> Display::create() {
    return std::make_unique<DisplayImplementation>();
}

}
