#pragma once

#include <storm/display.h>
#include <storm/platform/x11/display_connection_x11.h>

namespace storm {

class DisplayX11 : public Display {
public:
    DisplayX11();

    virtual Mode getDefaultMode() const;
    virtual std::vector<Mode> getSupportedModes() const;

private:
    DisplayConnection _display;
};

}
