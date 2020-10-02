#pragma once

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/query.h>

namespace storm {

using QueryHandleOgl = HandleOgl<GlGenQueries, GlDeleteQueries>;

class GpuTimeIntervalQueryOgl : public GpuTimeIntervalQuery {
public:
    explicit GpuTimeIntervalQueryOgl( GpuContextOgl::Pointer );

    void begin() override;
    void end() override;

    bool isResultReady() const override;

    std::chrono::nanoseconds getResult() const override;

private:
    QueryHandleOgl _beginTimestampQueryHandle;
    QueryHandleOgl _endTimestampQueryHandle;
    bool _running = false;
};

}
