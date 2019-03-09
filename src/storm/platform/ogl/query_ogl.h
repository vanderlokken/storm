#pragma once

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/query.h>

namespace storm {

class QueryHandleOgl : public HandleOgl {
public:
    QueryHandleOgl();
    ~QueryHandleOgl();
};

class GpuTimeIntervalQueryOgl : public GpuTimeIntervalQuery {
public:
    GpuTimeIntervalQueryOgl();

    void begin() override;
    void end() override;

    bool isResultReady() const override;

    std::chrono::nanoseconds getResult() const override;

private:
    QueryHandleOgl _beginTimestampQueryHandle;
    QueryHandleOgl _endTimestampQueryHandle;
    bool _running;
};

}
