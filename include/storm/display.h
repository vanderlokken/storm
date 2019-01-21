#pragma once

#include <memory>
#include <vector>

namespace storm {

class Display {
public:
    struct Mode {
        unsigned int width;
        unsigned int height;
        unsigned int refreshRate;
    };

    static std::unique_ptr<Display> create();

    virtual ~Display() {}

    virtual Mode getDefaultMode() const = 0;
    virtual std::vector<Mode> getSupportedModes() const = 0;
};

}
