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

    // Calls observer callbacks registered for input devices. This method should
    // be called from the 'callback', otherwise 'processInputEvents' will be
    // called automatically.
    virtual void processInputEvents() = 0;
};

}
