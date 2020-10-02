#include <storm/ogl/buffer_ogl.h>

#include <storm/ogl/resource_type_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

// GL_COPY_WRITE_BUFFER and GL_COPY_READ_BUFFER are not used in the rendering
// process so it's safe to overwrite these targets and to use them in the data
// transfer operations.

BufferOgl::BufferOgl(
        GpuContextOgl::Pointer gpuContext,
        const Description &description,
        const void *data ) :
    _description( description ),
    _handle( gpuContext )
{
    gpuContext->call<GlBindBuffer>( GL_COPY_WRITE_BUFFER, _handle );

    if( gpuContext->getExtensionSupportStatus().arbBufferStorage ) {
        const GLbitfield flags = GL_DYNAMIC_STORAGE_BIT;

        gpuContext->call<GlBufferStorage>(
            GL_COPY_WRITE_BUFFER, _description.size, data, flags );

    } else {
        const GLenum usage = getResourceUsage( _description.resourceType );

        gpuContext->call<GlBufferData>(
            GL_COPY_WRITE_BUFFER, _description.size, data, usage );
    }
}

void BufferOgl::getData( size_t offset, size_t size, void *data ) const {
    const GpuContextOgl &gpuContext = *_handle.getGpuContext();

    gpuContext.call<GlBindBuffer>(
        GL_COPY_READ_BUFFER, _handle );
    gpuContext.call<GlGetBufferSubData>(
        GL_COPY_READ_BUFFER, offset, size, data );
}

void BufferOgl::setData( size_t offset, size_t size, const void *data ) {
    storm_assert( offset + size <= _description.size );

    const GpuContextOgl &gpuContext = *_handle.getGpuContext();

    gpuContext.call<GlBindBuffer>(
        GL_COPY_WRITE_BUFFER, _handle );

    if( gpuContext.getExtensionSupportStatus().arbInvalidateSubdata ) {
        gpuContext.call<GlInvalidateBufferSubData>( _handle, offset, size );
    }

    gpuContext.call<GlBufferSubData>(
        GL_COPY_WRITE_BUFFER, offset, size, data );
}

const Buffer::Description& BufferOgl::getDescription() const {
    return _description;
}

const BufferHandleOgl& BufferOgl::getHandle() const {
    return _handle;
}

Buffer::Pointer Buffer::create(
    GpuContext::Pointer gpuContext,
    const Description &description,
    const void *data )
{
    return std::make_shared<BufferOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        description,
        data );
}

}
