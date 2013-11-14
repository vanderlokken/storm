#pragma once

#include <storm/index_buffer.h>
#include <storm/noncopyable.h>
#include <storm/platform/dx9/core_types_dx9.h>
#include <storm/platform/win/com_pointer.h>

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
