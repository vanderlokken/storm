#pragma once

#include <chrono>
#include <memory>

namespace storm {

class GpuTimeIntervalQuery {
public:
    typedef std::shared_ptr<GpuTimeIntervalQuery> Pointer;

    static Pointer create();

    virtual ~GpuTimeIntervalQuery() {}

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual bool isResultReady() const = 0;

    virtual std::chrono::nanoseconds getResult() const = 0;
};

}
