#include <storm/platform/ogl/index_buffer_ogl.h>

#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

IndexBufferOgl::IndexBufferOgl( const Description &description, const void *indices )
    : _description( description ),
      _buffer( description.bufferSize, indices, description.resourceType ),
      _indexFormat( selectIndexFormat(description.indexSize) )
{
    return;
}

void IndexBufferOgl::getIndices( size_t offset, size_t size, void *indices ) const {
    _buffer.getData( offset, size, indices );
    return;
}

void IndexBufferOgl::setIndices( size_t offset, size_t size, const void *indices ) {
    _buffer.setData( offset, size, indices );
    return;
}

const IndexBuffer::Description& IndexBufferOgl::getDescription() const noexcept {
    return _description;
}

const BufferHandleOgl& IndexBufferOgl::getHandle() const noexcept {
    return _buffer.getHandle();
}

GLenum IndexBufferOgl::getIndexFormat() const noexcept {
    return _indexFormat;
}

GLenum IndexBufferOgl::selectIndexFormat( size_t indexSize ) {
    switch( indexSize ) {
    case 2:
        return GL_UNSIGNED_SHORT;
    case 4:
        return GL_UNSIGNED_INT;
    default:
        throwInvalidArgument( "'indexSize' is invalid" );
    }
}

IndexBuffer::Pointer IndexBuffer::create(
    const Description &description, const void *indices )
{
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< IndexBufferOgl >( description, indices );
}

}
