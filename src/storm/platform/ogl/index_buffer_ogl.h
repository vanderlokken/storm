#pragma once

#include <storm/index_buffer.h>
#include <storm/platform/ogl/buffer_ogl.h>

namespace storm {

class IndexBufferOgl : public IndexBuffer {
    NONCOPYABLE( IndexBufferOgl );
public:
    IndexBufferOgl( const Description&, const void *indices = nullptr );

    virtual void getIndices( size_t offset, size_t size, void *indices ) const;
    virtual void setIndices( size_t offset, size_t size, const void *indices );

    virtual const Description& getDescription() const noexcept;

    const BufferHandleOgl& getHandle() const noexcept;
    GLenum getIndexFormat() const noexcept;

private:
    static GLenum selectIndexFormat( size_t indexSize );

    Description _description;
    BufferOgl _buffer;
    GLenum _indexFormat;
};

}
