#pragma once

#include <storm/display.h>

namespace storm {

class DisplayWin : public Display {
public:
    static DisplayWin* getInstance();

    virtual std::vector<Mode> getSupportedModes() const noexcept;

    virtual const Mode& getCurrentMode() const noexcept;
    virtual void setCurrentMode( const Mode& );

private:
    DisplayWin();

    Mode _currentMode;
};

}
