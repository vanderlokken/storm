#pragma once

#include <cstdint>

namespace storm {

class Clock {
public:
    typedef uint32_t Time;

    static Clock* getInstance();

    virtual ~Clock() { }

    virtual void update() = 0;

    virtual Time getTime() const = 0;
    virtual Time getTimeChange() const = 0;
};

}
