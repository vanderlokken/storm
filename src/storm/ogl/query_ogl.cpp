#include <storm/ogl/query_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

GpuTimeIntervalQueryOgl::GpuTimeIntervalQueryOgl(
        GpuContextOgl::Pointer gpuContext ) :
    _beginTimestampQueryHandle( gpuContext ),
    _endTimestampQueryHandle( gpuContext )
{
}

void GpuTimeIntervalQueryOgl::begin() {
    storm_assert( !_running );

    const GpuContextOgl &gpuContext =
        *_beginTimestampQueryHandle.getGpuContext();

    gpuContext.call<GlQueryCounter>(
        _beginTimestampQueryHandle, GL_TIMESTAMP );

    _running = true;
}

void GpuTimeIntervalQueryOgl::end() {
    storm_assert( _running );

    const GpuContextOgl &gpuContext =
        *_endTimestampQueryHandle.getGpuContext();

    gpuContext.call<GlQueryCounter>(
        _endTimestampQueryHandle, GL_TIMESTAMP );

    _running = false;
}

bool GpuTimeIntervalQueryOgl::isResultReady() const {
    storm_assert( !_running );

    const GpuContextOgl &gpuContext =
        *_beginTimestampQueryHandle.getGpuContext();

    GLint beginQueryReady;
    GLint endQueryReady;

    gpuContext.call<GlGetQueryObjectiv>(
        _beginTimestampQueryHandle, GL_QUERY_RESULT_AVAILABLE,
        &beginQueryReady );

    gpuContext.call<GlGetQueryObjectiv>(
        _endTimestampQueryHandle, GL_QUERY_RESULT_AVAILABLE, &endQueryReady );

    return beginQueryReady && endQueryReady;
}

std::chrono::nanoseconds GpuTimeIntervalQueryOgl::getResult() const {
    storm_assert( !_running );

    const GpuContextOgl &gpuContext =
        *_beginTimestampQueryHandle.getGpuContext();

    GLuint64 begin;
    GLuint64 end;

    gpuContext.call<GlGetQueryObjectui64v>(
        _beginTimestampQueryHandle, GL_QUERY_RESULT, &begin );

    gpuContext.call<GlGetQueryObjectui64v>(
        _endTimestampQueryHandle, GL_QUERY_RESULT, &end );

    return std::chrono::nanoseconds( end - begin );
}

GpuTimeIntervalQuery::Pointer GpuTimeIntervalQuery::create(
    GpuContext::Pointer gpuContext )
{
    auto context =
        std::dynamic_pointer_cast<GpuContextOgl>( std::move(gpuContext) );

    if( !context->getExtensionSupportStatus().arbTimerQuery ) {
        throw SystemRequirementsNotMet() <<
            "Video driver doesn't support 'ARB_timer_query' OpenGL extension.";
    }

    return std::make_shared<GpuTimeIntervalQueryOgl>( std::move(context) );
}

}
