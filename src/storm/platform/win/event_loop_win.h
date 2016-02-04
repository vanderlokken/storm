#pragma once

#include <storm/event_loop_common.h>
#include <storm/noncopyable.h>
#include <storm/platform/win/api_win.h>

namespace storm {

class EventLoopWin : public EventLoopCommon {
    NONCOPYABLE( EventLoopWin );
public:
    EventLoopWin();
    ~EventLoopWin();

    virtual void processEvents();

    static const WORD ToggleFullscreenModeCommand = 0;

private:
    HACCEL _acceleratorTableHandle;
};

}
