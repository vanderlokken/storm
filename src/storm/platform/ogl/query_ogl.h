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

    virtual void begin();
    virtual void end();

    virtual bool isResultReady() const;

    virtual std::chrono::nanoseconds getResult() const;

private:
    QueryHandleOgl _beginTimestampQueryHandle;
    QueryHandleOgl _endTimestampQueryHandle;
    bool _running;
};

}
