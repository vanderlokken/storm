#pragma once

#include <functional>

namespace storm {

class EventLoop {
public:
    typedef std::function<void ()> Callback;

    static EventLoop* getInstance();

    virtual ~EventLoop() {}

    // Calls 'callback' and then 'processEvents' if it wasn't called in
    // a 'callback'. Blocks and continuously repeats this algorithm until 'stop'
    // is called.
    virtual void run( const Callback &callback ) = 0;
    virtual void stop() = 0;

    // Process queued events (i.e. calls callbacks registred in classes like
    // 'Keyboard::Observer' or 'Mouse::Observer'). This method can be called
    // automatically by the 'run' method or it can be called manually at any
    // time.
    virtual void processEvents() = 0;
};

}
