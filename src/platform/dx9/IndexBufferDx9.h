#ifndef storm_IndexBufferDx9_h
#define storm_IndexBufferDx9_h

#include "CoreTypesDx9.h"
#include "IndexBuffer.h"
#include "Noncopyable.h"
#include "platform/win/ComPointer.h"

struct IDirect3DIndexBuffer9;

namespace storm {

class IndexBufferDx9 : public IndexBuffer {
    NONCOPYABLE( IndexBufferDx9 );
public:
    IndexBufferDx9( const Description&, const void *indices );
    
    virtual void setIndices( size_t offset, size_t size, const void *indices );
    virtual void getIndices( size_t offset, size_t size, void *indices ) const;
    
    virtual const Description& getDescription() const noexcept;
    
    ComPointer< IDirect3DIndexBuffer9 > getBuffer() const noexcept;
    
private:
    static D3DFORMAT selectFormat( size_t indexSize );
    
    Description _description;
    ComPointer< IDirect3DIndexBuffer9 > _buffer;
};

}

#endif