#pragma once

#include <sys/time.h>

#include <storm/clock.h>

namespace storm {

class ClockPosix : public Clock {
public:
    static ClockPosix* getInstance();

    virtual ~ClockPosix() { }

    virtual void update();

    virtual Time getTime() const;
    virtual Time getTimeChange() const;

private:
    ClockPosix();

    uint64_t _systemTime;
    uint64_t _previousSystemTime;
    uint64_t _initialSystemTime;

    static const uint64_t MicrosecondsPerSecond = 1000000;
    static const uint64_t MicrosecondsPerMillisecond = 1000;
};

}
