#ifndef storm_FrameworkWin_h
#define storm_FrameworkWin_h

#include "Framework.h"
#include "Noncopyable.h"

namespace storm {

class FrameworkWin : public Framework {
    NONCOPYABLE( FrameworkWin );
public:
    static std::shared_ptr<FrameworkWin> getInstance();

    virtual void run( const Callback &callback );
    virtual void stop();

private:
    FrameworkWin() noexcept;
};

}

#endif