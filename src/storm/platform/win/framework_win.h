#pragma once

#include <storm/framework.h>
#include <storm/noncopyable.h>

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
