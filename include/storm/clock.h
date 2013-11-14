#pragma once

#include <cstdint>

#include <storm/noexcept.h>

namespace storm {

class Clock {
public:
    typedef uint32_t Time;

    static Clock* getInstance();

    virtual ~Clock() { }

    virtual void update() noexcept = 0;

    virtual Time getTime() const noexcept = 0;
    virtual Time getTimeChange() const noexcept = 0;
};

}
