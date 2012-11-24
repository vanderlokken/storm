#include "HighPrecisionClock.h"

namespace storm {

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

HighPrecisionClock::HighPrecisionClock()
    : _start( high_resolution_clock::now() ), _timePoint( _start ), _timeChange( 0 )
{
}

void HighPrecisionClock::update() noexcept {
    const auto newTimePoint = high_resolution_clock::now();
    _timeChange = newTimePoint - _timePoint;
    _timePoint = newTimePoint;
}

Clock::Time HighPrecisionClock::getTime() const noexcept {
    return static_cast<Clock::Time>(
        duration_cast<milliseconds>( _timePoint - _start ).count()
    );
}

Clock::Time HighPrecisionClock::getTimeChange() const noexcept {
    return static_cast<Clock::Time>(
        duration_cast<milliseconds>( _timeChange ).count()
    );
}

std::shared_ptr<Clock> Clock::getInstance() {
    static const std::shared_ptr<Clock> instance( std::make_shared<HighPrecisionClock>() );
    return instance;
}

}
