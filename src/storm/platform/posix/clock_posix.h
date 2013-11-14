#pragma once

#include <sys/time.h>

#include <storm/clock.h>

namespace storm {

class ClockPosix : public Clock {
public:
    static std::shared_ptr<ClockPosix> getInstance();

    virtual ~ClockPosix() { }

    virtual void update() noexcept;

    virtual Time getTime() const noexcept;
    virtual Time getTimeChange() const noexcept;

private:
    ClockPosix() noexcept;

    uint64_t _systemTime;
    uint64_t _previousSystemTime;
    uint64_t _initialSystemTime;

    static const uint64_t MicrosecondsPerSecond = 1000000;
    static const uint64_t MicrosecondsPerMillisecond = 1000;
};

}
