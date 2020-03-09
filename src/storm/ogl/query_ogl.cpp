#include <storm/ogl/query_ogl.h>

#include <storm/ogl/check_result_ogl.h>
#include <storm/ogl/rendering_system_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

QueryHandleOgl::QueryHandleOgl() {
    ::glGenQueries( 1, &_handle );
    checkResult( "::glGenQueries" );
}

QueryHandleOgl::~QueryHandleOgl() {
    ::glDeleteQueries( 1, &_handle );
}

GpuTimeIntervalQueryOgl::GpuTimeIntervalQueryOgl() : _running( false ) {}

void GpuTimeIntervalQueryOgl::begin() {
    storm_assert( !_running );

    ::glQueryCounter( _beginTimestampQueryHandle, GL_TIMESTAMP );
    checkResult( "::glQueryCounter" );

    _running = true;
}

void GpuTimeIntervalQueryOgl::end() {
    storm_assert( _running );

    ::glQueryCounter( _endTimestampQueryHandle, GL_TIMESTAMP );
    checkResult( "::glQueryCounter" );

    _running = false;
}

bool GpuTimeIntervalQueryOgl::isResultReady() const {
    storm_assert( !_running );

    GLint beginQueryReady;
    GLint endQueryReady;

    ::glGetQueryObjectiv(
        _beginTimestampQueryHandle, GL_QUERY_RESULT_AVAILABLE,
        &beginQueryReady );
    checkResult( "::glGetQueryObjectiv" );

    ::glGetQueryObjectiv(
        _endTimestampQueryHandle, GL_QUERY_RESULT_AVAILABLE, &endQueryReady );
    checkResult( "::glGetQueryObjectiv" );

    return beginQueryReady && endQueryReady;
}

std::chrono::nanoseconds GpuTimeIntervalQueryOgl::getResult() const {
    storm_assert( !_running );

    GLuint64 begin;
    GLuint64 end;

    ::glGetQueryObjectui64v(
        _beginTimestampQueryHandle, GL_QUERY_RESULT, &begin );
    checkResult( "::glGetQueryObjectui64v" );

    ::glGetQueryObjectui64v(
        _endTimestampQueryHandle, GL_QUERY_RESULT, &end );
    checkResult( "::glGetQueryObjectui64v" );

    return std::chrono::nanoseconds( end - begin );
}

GpuTimeIntervalQuery::Pointer GpuTimeIntervalQuery::create() {
    RenderingSystemOgl::installOpenGlContext();

    if( !getOpenGlSupportStatus().ARB_timer_query )
        throw SystemRequirementsNotMet() <<
            "Video driver doesn't support 'ARB_timer_query' OpenGL extension.";

    return std::make_shared<GpuTimeIntervalQueryOgl>();
}

}
