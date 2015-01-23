#pragma once

#include <storm/platform/win/api_win.h>

#include <mmsystem.h>

namespace storm {

class MultimediaClockWin {
public:
    MultimediaClockWin();
    ~MultimediaClockWin();

    DWORD now();

private:
    DWORD _applicationTime;
    DWORD _systemTime;

    typedef MMRESULT (WINAPI *TimeBeginPeriodPointer)( UINT );
    typedef MMRESULT (WINAPI *TimeEndPeriodPointer)( UINT );
    typedef DWORD (WINAPI *TimeGetTimePointer)();

    TimeBeginPeriodPointer _timeBeginPeriod;
    TimeEndPeriodPointer _timeEndPeriod;
    TimeGetTimePointer _timeGetTime;

    static const UINT Period = 1;
};

}
