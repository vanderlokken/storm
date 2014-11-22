#pragma once

#include <storm/clock.h>
#include <storm/platform/win/api_win.h>

#include <mmsystem.h>

namespace storm {

class MultimediaClockWin : public Clock {
public:
    static MultimediaClockWin* getInstance();

    virtual ~MultimediaClockWin();

    virtual void update();

    virtual Time getTime() const;
    virtual Time getTimeChange() const;

private:
    MultimediaClockWin();

    Time _time;
    Time _timeChange;

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
