#include "BufferOgl.h"

#include <cstring>

#include "CheckResultOgl.h"
#include "ResourceTypeOgl.h"

namespace storm {

BufferHandleOgl::BufferHandleOgl() {
    ::glGenBuffers( 1, &_handle );
    checkResult( "::glGenBuffers" );
    return;
}

BufferHandleOgl::~BufferHandleOgl() noexcept {
    ::glDeleteBuffers( 1, &_handle );
    return;
}

// GL_COPY_WRITE_BUFFER and GL_COPY_READ_BUFFER are not used in the rendering process
// so it's safe to overwrite these targets and to use them in the data transfer operations.

BufferOgl::BufferOgl( size_t size, const void *data, ResourceType resourceType )
    : _size( size )
{
    ::glBindBuffer( GL_COPY_WRITE_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    const GLenum usage = getResourceUsage( resourceType );

    ::glBufferData( GL_COPY_WRITE_BUFFER, size, data, usage );
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
    if( offset + size > _size ) {
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

const BufferHandleOgl& BufferOgl::getHandle() const noexcept {
    return _handle;
}

}
