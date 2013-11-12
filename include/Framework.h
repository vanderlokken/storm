#pragma once

#include <functional>
#include <memory>

#include "Noexcept.h"

namespace storm {

class Framework {
public:
    typedef std::function< void () > Callback;

    static std::shared_ptr<Framework> getInstance();

    virtual ~Framework() { }

    virtual void run( const Callback &callback ) = 0;
    virtual void stop() = 0;
};

}
