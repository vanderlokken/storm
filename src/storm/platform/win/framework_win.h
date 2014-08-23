#pragma once

#include <storm/framework.h>
#include <storm/noncopyable.h>

namespace storm {

class FrameworkWin : public Framework {
    NONCOPYABLE( FrameworkWin );
public:
    static FrameworkWin* getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

    virtual void processInputEvents();

private:
    FrameworkWin();

    bool _running;
    bool _eventsProcessed;
};

}
