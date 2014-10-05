#pragma once

#include <storm/event_loop_common.h>
#include <storm/noncopyable.h>

namespace storm {

class EventLoopWin : public EventLoopCommon {
    NONCOPYABLE( EventLoopWin );
public:
    EventLoopWin() = default;

    virtual void processEvents();
};

}
