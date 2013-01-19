#ifndef storm_Framework_h
#define storm_Framework_h

#include <functional>
#include <memory>

#include "Noexcept.h"

namespace storm {

class Framework {
public:
    typedef std::function< void () > Callback;

    static std::shared_ptr<Framework> getInstance();

    virtual ~Framework() noexcept { }

    virtual void run( const Callback &callback ) = 0;
    virtual void stop() = 0;
};

}

#endif