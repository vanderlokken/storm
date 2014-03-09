#pragma once

#include <storm/display.h>

namespace storm {

class DisplayWin : public Display {
public:
    static DisplayWin* getInstance();

    virtual std::vector<Mode> getSupportedModes() const;

    virtual const Mode& getCurrentMode() const;
    virtual void setCurrentMode( const Mode& );

private:
    DisplayWin();

    Mode _currentMode;
};

}
