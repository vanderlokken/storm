#include "VertexBufferOgl.h"

namespace storm {

VertexBufferOgl::VertexBufferOgl( const Description &description, const void *vertices )
    : _description( description ),
      _buffer( description.bufferSize, vertices, description.resourceType )
{
    return;
}

void VertexBufferOgl::getVertices( size_t offset, size_t size, void *vertices ) const {
    _buffer.getData( offset, size, vertices );
    return;
}
void VertexBufferOgl::setVertices( size_t offset, size_t size, const void *vertices ) {
    _buffer.setData( offset, size, vertices );
    return;
}

const VertexBuffer::Description& VertexBufferOgl::getDescription() const noexcept {
    return _description;
}

GLuint VertexBufferOgl::getHandle() const noexcept {
    return _buffer.getHandle();
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(
    const Description &description, const void *vertices )
{
    return std::make_shared< VertexBufferOgl >( description, vertices );
}

}