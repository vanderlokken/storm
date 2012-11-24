#ifndef storm_DisplayWin_h
#define storm_DisplayWin_h

#include "Display.h"

namespace storm {

class DisplayWin : public Display {
public:
    static std::shared_ptr<DisplayWin> getInstance();
    
    virtual std::vector<Mode> getSupportedModes() const noexcept;
    
    virtual const Mode& getCurrentMode() const noexcept;
    virtual void setCurrentMode( const Mode& );
    
private:
    DisplayWin();
    
    Mode _currentMode;
};

}

#endif