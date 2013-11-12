#pragma once

#include <cstdint>
#include <memory>

#include "Noexcept.h"

namespace storm {

class Clock {
public:
    typedef uint32_t Time;

    static std::shared_ptr<Clock> getInstance();

    virtual ~Clock() { }

    virtual void update() noexcept = 0;

    virtual Time getTime() const noexcept = 0;
    virtual Time getTimeChange() const noexcept = 0;
};

}
