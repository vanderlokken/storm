#ifndef storm_VertexBufferOgl_h
#define storm_VertexBufferOgl_h

#include "BufferOgl.h"
#include "VertexBuffer.h"

namespace storm {

class VertexBufferOgl : public VertexBuffer {
    NONCOPYABLE( VertexBufferOgl );
public:
    VertexBufferOgl( const Description&, const void *vertices = nullptr );
    
    virtual ~VertexBufferOgl() noexcept { }

    virtual void getVertices( size_t offset, size_t size, void *vertices ) const;
    virtual void setVertices( size_t offset, size_t size, const void *vertices );
    
    virtual const Description& getDescription() const noexcept;
    
    GLuint getHandle() const noexcept;
    
private:
    Description _description;
    BufferOgl _buffer;
};

}

#endif
