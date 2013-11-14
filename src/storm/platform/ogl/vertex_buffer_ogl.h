#pragma once

#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/vertex_buffer.h>

namespace storm {

class VertexBufferOgl : public VertexBuffer {
    NONCOPYABLE( VertexBufferOgl );
public:
    VertexBufferOgl( const Description&, const void *vertices = nullptr );

    virtual void getVertices( size_t offset, size_t size, void *vertices ) const;
    virtual void setVertices( size_t offset, size_t size, const void *vertices );

    virtual const Description& getDescription() const noexcept;

    const BufferHandleOgl& getHandle() const noexcept;

private:
    Description _description;
    BufferOgl _buffer;
};

}
