#include <storm/platform/posix/clock_posix.h>

#include <memory>

namespace storm {

ClockPosix::ClockPosix() noexcept
    : _systemTime( 0 ),
      _previousSystemTime( 0 ),
      _initialSystemTime( 0 )
{
    timeval time;
    gettimeofday( &time, nullptr );

    _initialSystemTime = time.tv_sec * MicrosecondsPerSecond + time.tv_usec;

    _systemTime = _initialSystemTime;
    _previousSystemTime = _initialSystemTime;
    return;
}

void ClockPosix::update() noexcept {
    timeval time;
    gettimeofday( &time, nullptr );

    uint64_t newSystemTime = time.tv_sec * MicrosecondsPerSecond + time.tv_usec;

    _previousSystemTime = _systemTime;
    if( newSystemTime - _systemTime >= MicrosecondsPerMillisecond )
        _systemTime = newSystemTime;
    return;
}

Clock::Time ClockPosix::getTime() const noexcept {
    return (_systemTime - _initialSystemTime) / MicrosecondsPerMillisecond;
}

Clock::Time ClockPosix::getTimeChange() const noexcept {
    return (_systemTime - _previousSystemTime) / MicrosecondsPerMillisecond;
}

ClockPosix* ClockPosix::getInstance() {
    static const std::unique_ptr<ClockPosix> instance( new ClockPosix );
    return instance.get();
}

Clock* Clock::getInstance() {
    return ClockPosix::getInstance();
}

}
