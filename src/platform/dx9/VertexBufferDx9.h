#ifndef storm_VertexBufferDx9_h
#define storm_VertexBufferDx9_h

#include "Noncopyable.h"
#include "platform/win/ComPointer.h"
#include "VertexBuffer.h"

struct IDirect3DVertexBuffer9;
struct IDirect3DVertexDeclaration9;

namespace storm {

class VertexBufferDx9 : public VertexBuffer {
    NONCOPYABLE( VertexBufferDx9 );
public:
    VertexBufferDx9( const Description&, const void *vertices = nullptr );

    virtual void getVertices( size_t offset, size_t size, void *vertices ) const;
    virtual void setVertices( size_t offset, size_t size, const void *vertices );

    virtual const Description& getDescription() const noexcept;

    ComPointer< IDirect3DVertexBuffer9 > getBuffer() const noexcept;
    ComPointer< IDirect3DVertexDeclaration9 > getVertexDeclaration() const noexcept;

private:
    Description _description;
    ComPointer< IDirect3DVertexBuffer9 > _buffer;
    ComPointer< IDirect3DVertexDeclaration9 > _vertexDeclaration;
};

}

#endif