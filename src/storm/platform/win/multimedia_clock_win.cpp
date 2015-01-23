#include <storm/platform/win/multimedia_clock_win.h>

#include <storm/clock.h>
#include <storm/throw_exception.h>

namespace storm {

MultimediaClockWin::MultimediaClockWin() :
    _applicationTime( 0 ),
    _systemTime( 0 ),
    _timeBeginPeriod( nullptr ),
    _timeEndPeriod( nullptr ),
    _timeGetTime( nullptr )
{
    const HMODULE library = ::LoadLibrary( L"winmm.dll" );
    if( !library ) {
        throwRuntimeError( "Winmm.dll is not found" );
    }

    FARPROC timeBeginPeriodAddress = ::GetProcAddress( library, "timeBeginPeriod" );
    FARPROC timeEndPeriodAddress = ::GetProcAddress( library, "timeEndPeriod" );
    FARPROC timeGetTimeAddress = ::GetProcAddress( library, "timeGetTime" );

    _timeBeginPeriod = reinterpret_cast< TimeBeginPeriodPointer >( timeBeginPeriodAddress );
    _timeEndPeriod = reinterpret_cast< TimeEndPeriodPointer >( timeEndPeriodAddress );
    _timeGetTime = reinterpret_cast< TimeGetTimePointer >( timeGetTimeAddress );

    if( !_timeBeginPeriod || !_timeEndPeriod || !_timeGetTime ) {
        throwRuntimeError( "A required library function is missing" );
    }

    const MMRESULT result = _timeBeginPeriod( Period );
    if( result != TIMERR_NOERROR ) {
        throwRuntimeError( "::timeBeginPeriod has failed" );
    }

    _systemTime = _timeGetTime();
}

MultimediaClockWin::~MultimediaClockWin() {
    _timeEndPeriod( Period );
}

DWORD MultimediaClockWin::now() {
    const DWORD systemTime = _timeGetTime();

    if( systemTime >= _systemTime )
        _applicationTime += systemTime - _systemTime;
    else
        _applicationTime += (0xFFFFFFFF - _systemTime) + systemTime;

    _systemTime = systemTime;

    return _applicationTime;
}

namespace internal {
high_resolution_clock::time_point high_resolution_clock::now() {
    static MultimediaClockWin clock;
    return time_point( duration(clock.now()) );
}
} // namespace internal

}
