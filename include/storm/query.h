#pragma once

#include <chrono>
#include <memory>

namespace storm {

class GpuTimeIntervalQuery {
public:
    using Pointer = std::shared_ptr<GpuTimeIntervalQuery>;

    static Pointer create();

    virtual ~GpuTimeIntervalQuery() = default;

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual bool isResultReady() const = 0;

    virtual std::chrono::nanoseconds getResult() const = 0;
};

}
