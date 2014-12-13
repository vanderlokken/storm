#pragma once

#include <storm/display.h>
#include <storm/platform/win/api_win.h>

namespace storm {

class DisplayWin : public Display {
public:
    virtual Mode getDefaultMode() const;
    virtual std::vector<Mode> getSupportedModes() const;

private:
    static Mode convertMode( const DEVMODE& );
};

}
