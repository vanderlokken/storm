#include <storm/platform/win/api_win.h>

#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )

#include <storm/clock.h>

namespace storm {

class ClockWin {
public:
    static const UINT Period = 1;

    ClockWin() :
        _initialSystemTime( ::timeGetTime() )
    {
        ::timeBeginPeriod( Period );
    }

    ~ClockWin() {
        ::timeEndPeriod( Period );
    }

    DWORD now() const {
        const DWORD systemTime = ::timeGetTime();

        if( systemTime >= _initialSystemTime )
            return systemTime - _initialSystemTime;
        else
            return (0xFFFFFFFF - _initialSystemTime) + systemTime;
    }

private:
    DWORD _initialSystemTime;
};

namespace internal {
high_resolution_clock::time_point high_resolution_clock::now() {
    static const ClockWin clock;
    return time_point( duration(clock.now()) );
}
} // namespace internal

}
