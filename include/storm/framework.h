#pragma once

#include <functional>

namespace storm {

class Framework {
public:
    typedef std::function< void () > Callback;

    static Framework* getInstance();

    virtual ~Framework() { }

    virtual void run( const Callback &callback ) = 0;
    virtual void stop() = 0;
};

}
