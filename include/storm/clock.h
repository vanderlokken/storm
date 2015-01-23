#pragma once

#include <chrono>
#include <ratio>

namespace storm {
namespace internal {

class high_resolution_clock {
public:
    // This class has stl-compatible interface and represents a reliable
    // alternative to std::chrono::high_resolution_clock which is allowed to be
    // implemented as an alias to std::chrono::system_clock.
    typedef unsigned int rep;
    typedef std::milli period;
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<high_resolution_clock> time_point;

    static const bool is_steady = true;

    static time_point now();
};

} // namespace internal

class Clock {
public:
    typedef internal::high_resolution_clock::time_point TimePoint;
    typedef internal::high_resolution_clock::duration TimeDelta;

    static TimePoint now() {
        return internal::high_resolution_clock::now();
    }
};

}
