#include <storm/platform/ogl/index_buffer_ogl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/constants_ogl.h>

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
    GLenum result;

    switch( indexSize ) {
    case 2:
        result = GL_UNSIGNED_SHORT;
        break;

    case 4:
        result = GL_UNSIGNED_INT;
        break;

    default:
        throwInvalidArgument( "'indexSize' is invalid" );
    }
    return result;
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(
    const Description &description, const void *indices )
{
    return std::make_shared< IndexBufferOgl >( description, indices );
}

}