#ifndef storm_IndexBufferOgl_h
#define storm_IndexBufferOgl_h

#include "BufferOgl.h"
#include "IndexBuffer.h"

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

#endif