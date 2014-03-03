#include <storm/platform/ogl/buffer_ogl.h>

#include <cstring>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/resource_type_ogl.h>

namespace storm {

BufferHandleOgl::BufferHandleOgl() {
    ::glGenBuffers( 1, &_handle );
    checkResult( "::glGenBuffers" );
    return;
}

BufferHandleOgl::~BufferHandleOgl() {
    ::glDeleteBuffers( 1, &_handle );
    return;
}

// GL_COPY_WRITE_BUFFER and GL_COPY_READ_BUFFER are not used in the rendering process
// so it's safe to overwrite these targets and to use them in the data transfer operations.

BufferOgl::BufferOgl( const Description &description, const void *data )
    : _description( description )
{
    ::glBindBuffer( GL_COPY_WRITE_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    const GLenum usage = getResourceUsage( _description.resourceType );

    ::glBufferData( GL_COPY_WRITE_BUFFER, _description.size, data, usage );
    checkResult( "::glBufferData" );

    return;
}

void BufferOgl::getData( size_t offset, size_t size, void *data ) const {
    ::glBindBuffer( GL_COPY_READ_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    ::glGetBufferSubData( GL_COPY_READ_BUFFER, offset, size, data );
    checkResult( "::glGetBufferSubData" );
    return;
}

void BufferOgl::setData( size_t offset, size_t size, const void *data ) {
    if( offset + size > _description.size ) {
        throwInvalidArgument( "The specified offset and size are not correct" );
    }

    ::glBindBuffer( GL_COPY_WRITE_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    void *destination = ::glMapBufferRange( GL_COPY_WRITE_BUFFER, offset, size, GL_MAP_WRITE_BIT );
    checkResult( "::glMapBufferRange" );

    ::memcpy( destination, data, size );

    ::glUnmapBuffer( GL_COPY_WRITE_BUFFER );
    checkResult( "::glUnmapBuffer" );

    // glUnmapBuffer can return 'false' indicating the data corruption.
    // Now the return value is simply ignored.
    return;
}

const Buffer::Description& BufferOgl::getDescription() const noexcept {
    return _description;
}

const BufferHandleOgl& BufferOgl::getHandle() const noexcept {
    return _handle;
}

Buffer::Pointer Buffer::create(
    const Description &description, const void *data )
{
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared<BufferOgl>( description, data );
}

}
