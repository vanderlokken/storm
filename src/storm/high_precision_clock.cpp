#include <storm/high_precision_clock.h>

#include <memory>

namespace storm {

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

HighPrecisionClock::HighPrecisionClock()
    : _start( high_resolution_clock::now() ), _timePoint( _start ), _timeChange( 0 )
{
}

void HighPrecisionClock::update() {
    const auto newTimePoint = high_resolution_clock::now();
    _timeChange = newTimePoint - _timePoint;
    _timePoint = newTimePoint;
}

Clock::Time HighPrecisionClock::getTime() const {
    return static_cast<Clock::Time>(
        duration_cast<milliseconds>( _timePoint - _start ).count()
    );
}

Clock::Time HighPrecisionClock::getTimeChange() const {
    return static_cast<Clock::Time>(
        duration_cast<milliseconds>( _timeChange ).count()
    );
}

Clock* Clock::getInstance() {
    static const std::unique_ptr<Clock> instance( new HighPrecisionClock );
    return instance.get();
}

}
