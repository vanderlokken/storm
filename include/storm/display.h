#pragma once

#include <vector>

#include <storm/noexcept.h>

namespace storm {

class Display {
public:
    struct Mode {
        int width;
        int height;
        int refreshRate;
        int colorDepth;
    };

    static Display* getInstance();

    virtual ~Display() { }

    virtual std::vector<Mode> getSupportedModes() const noexcept = 0;

    virtual const Mode& getCurrentMode() const noexcept = 0;
    virtual void setCurrentMode( const Mode& ) = 0;
};

}
