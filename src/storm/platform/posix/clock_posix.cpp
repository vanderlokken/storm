#include <storm/clock.h>

#include <sys/time.h>

namespace storm {

namespace {
std::chrono::microseconds getSystemTime() {
    timeval time;
    gettimeofday( &time, nullptr );

    return std::chrono::seconds( time.tv_sec ) +
        std::chrono::microseconds( time.tv_usec );
}
} // namespace

namespace internal {
high_resolution_clock::time_point high_resolution_clock::now() {
    static const std::chrono::microseconds initialSystemTime = getSystemTime();
    const std::chrono::microseconds systemTime = getSystemTime();
    return time_point(
        std::chrono::duration_cast<duration>(systemTime - initialSystemTime) );
}
} // namespace internal

}
