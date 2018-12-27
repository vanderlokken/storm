#pragma once

#include <memory>
#include <vector>

#include <storm/window.h>

namespace storm {

class ProxyWindowObserver {
public:
    ProxyWindowObserver();

    ProxyWindowObserver( const ProxyWindowObserver& ) = delete;
    ProxyWindowObserver& operator = ( const ProxyWindowObserver& ) = delete;

    ProxyWindowObserver( ProxyWindowObserver&& ) = default;
    ProxyWindowObserver& operator = ( ProxyWindowObserver&& ) = default;

    void addObserver( std::weak_ptr<WindowObserver> observer );

    const WindowObserver* operator -> () const;

private:
    void update();

    std::shared_ptr<std::vector<std::weak_ptr<WindowObserver>>> _observers;

    WindowObserver _observer;
};

}
