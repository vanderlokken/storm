#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include <mmsystem.h>

#include "Clock.h"

namespace storm {

class MultimediaClockWin : public Clock {
public:
    static std::shared_ptr<MultimediaClockWin> getInstance();

    virtual ~MultimediaClockWin();

    virtual void update() noexcept;

    virtual Time getTime() const noexcept;
    virtual Time getTimeChange() const noexcept;

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
