#include <storm/platform/win/multimedia_clock_win.h>

#include <memory>

#include <storm/exception.h>

namespace storm {

MultimediaClockWin::MultimediaClockWin()
    : _time( 0 ),
      _timeChange( 0 ),
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
    return;
}

MultimediaClockWin::~MultimediaClockWin() {
    _timeEndPeriod( Period );
    return;
}

void MultimediaClockWin::update() noexcept {
    DWORD currentSystemTime = _timeGetTime();

    if( _systemTime != 0 ) {
        if( currentSystemTime >= _systemTime ) {
            _timeChange = currentSystemTime - _systemTime;
        } else {
            _timeChange = ( 0xFFFFFFFF - _systemTime ) + currentSystemTime;
        }
        _time += _timeChange;
    }
    _systemTime = currentSystemTime;
    return;
}

Clock::Time MultimediaClockWin::getTime() const noexcept {
    return _time;
}

Clock::Time MultimediaClockWin::getTimeChange() const noexcept {
    return _timeChange;
}

MultimediaClockWin* MultimediaClockWin::getInstance() {
    static const std::unique_ptr<MultimediaClockWin> instance( new MultimediaClockWin );
    return instance.get();
}

Clock* Clock::getInstance() {
    return MultimediaClockWin::getInstance();
}

}