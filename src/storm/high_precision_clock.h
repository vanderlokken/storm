#pragma once

#include <chrono>

#include <storm/clock.h>

namespace storm {

class HighPrecisionClock : public Clock {
public:
    HighPrecisionClock();

    virtual void update() noexcept;

    virtual Time getTime() const noexcept;
    virtual Time getTimeChange() const noexcept;

private:
    std::chrono::high_resolution_clock::time_point _start;
    std::chrono::high_resolution_clock::time_point _timePoint;
    std::chrono::high_resolution_clock::duration _timeChange;
};

}
