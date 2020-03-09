#include <storm/ogl/buffer_ogl.h>

#include <storm/ogl/api_ogl.h>
#include <storm/ogl/check_result_ogl.h>
#include <storm/ogl/rendering_system_ogl.h>
#include <storm/ogl/resource_type_ogl.h>

namespace storm {

BufferHandleOgl::BufferHandleOgl() {
    ::glGenBuffers( 1, &_handle );
    checkResult( "::glGenBuffers" );
}

BufferHandleOgl::~BufferHandleOgl() {
    ::glDeleteBuffers( 1, &_handle );
}

// GL_COPY_WRITE_BUFFER and GL_COPY_READ_BUFFER are not used in the rendering
// process so it's safe to overwrite these targets and to use them in the data
// transfer operations.

BufferOgl::BufferOgl( const Description &description, const void *data ) :
    _description( description )
{
    ::glBindBuffer( GL_COPY_WRITE_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    if( getOpenGlSupportStatus().ARB_buffer_storage ) {
        const GLbitfield flags = GL_DYNAMIC_STORAGE_BIT;

        ::glBufferStorage(
            GL_COPY_WRITE_BUFFER, _description.size, data, flags );
        checkResult( "::glBufferStorage" );

    } else {
        const GLenum usage = getResourceUsage( _description.resourceType );

        ::glBufferData( GL_COPY_WRITE_BUFFER, _description.size, data, usage );
        checkResult( "::glBufferData" );
    }
}

void BufferOgl::getData( size_t offset, size_t size, void *data ) const {
    ::glBindBuffer( GL_COPY_READ_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    ::glGetBufferSubData( GL_COPY_READ_BUFFER, offset, size, data );
    checkResult( "::glGetBufferSubData" );
}

void BufferOgl::setData( size_t offset, size_t size, const void *data ) {
    storm_assert( offset + size <= _description.size );

    ::glBindBuffer( GL_COPY_WRITE_BUFFER, _handle );
    checkResult( "::glBindBuffer" );

    if( getOpenGlSupportStatus().ARB_invalidate_subdata ) {
        ::glInvalidateBufferSubData( _handle, offset, size );
        checkResult( "::glInvalidateBufferSubData" );
    }

    ::glBufferSubData( GL_COPY_WRITE_BUFFER, offset, size, data );
    checkResult( "::glBufferSubData" );
}

const Buffer::Description& BufferOgl::getDescription() const {
    return _description;
}

const BufferHandleOgl& BufferOgl::getHandle() const {
    return _handle;
}

Buffer::Pointer Buffer::create(
    const Description &description, const void *data )
{
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared<BufferOgl>( description, data );
}

}
