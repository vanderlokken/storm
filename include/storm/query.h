#pragma once

#include <chrono>
#include <memory>

#include <storm/gpu_context.h>

namespace storm {

class GpuTimeIntervalQuery {
public:
    using Pointer = std::shared_ptr<GpuTimeIntervalQuery>;

    static Pointer create( GpuContext::Pointer gpuContext );

    virtual ~GpuTimeIntervalQuery() = default;

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual bool isResultReady() const = 0;

    virtual std::chrono::nanoseconds getResult() const = 0;
};

}
