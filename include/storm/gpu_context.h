#pragma once

#include <memory>

namespace storm {

class GpuContext {
public:
    using Pointer = std::shared_ptr<GpuContext>;

    static Pointer create();

    virtual ~GpuContext() = default;
};

}
