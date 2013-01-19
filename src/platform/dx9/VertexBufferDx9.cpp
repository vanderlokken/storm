#include "VertexBufferDx9.h"

#include <numeric>

#include <d3d9.h>

#include "platform/win/CheckResult.h"
#include "RenderingSystemDx9.h"
#include "ResourceTypeDx9.h"
#include "VertexDx9.h"

namespace storm {

VertexBufferDx9::VertexBufferDx9( const Description &description, const void *vertices )
    : _description( description ),
      _vertexDeclaration( convertVertexAttributes(description.vertexAttributes) )
{
    ComPointer< IDirect3DDevice9 > device = RenderingSystemDx9::getDevice();

    const UINT size = description.bufferSize;
    const DWORD usage = selectResourceUsage( description.resourceType );
    const D3DPOOL pool = selectResourcePool( description.resourceType );

    // A flexible vertex format is not used. A vertex declaration is used instead
    const DWORD vertexFormat = 0;

    const HRESULT result = device->CreateVertexBuffer(
        size, usage, vertexFormat, pool, _buffer.getAddress(), nullptr );

    checkResult( result, "IDirect3DDevice9::CreateVertexBuffer" );

    if( vertices ) {
        setVertices( 0, description.bufferSize, vertices );
    }
    return;
}

void VertexBufferDx9::getVertices( size_t offset, size_t size, void *vertices ) const {

    if( size > _description.bufferSize )
        throwInvalidArgument( "'size' is invalid" );

    if( offset > _description.bufferSize )
        throwInvalidArgument( "'offset' is invalid" );

    if( offset + size > _description.bufferSize )
        throwInvalidArgument( "'offset' and 'size' are invalid" );

    void *data = nullptr;

    const HRESULT lockResult = _buffer->Lock( offset, size, &data, D3DLOCK_READONLY );
    checkResult( lockResult, "IDirect3DVertexBuffer9::Lock" );

    std::memcpy( vertices, data, size );

    const HRESULT unlockResult = _buffer->Unlock();
    checkResult( unlockResult, "IDirect3DVertexBuffer9::Unlock" );

    return;
}

void VertexBufferDx9::setVertices( size_t offset, size_t size, const void *vertices ) {

    if( size > _description.bufferSize )
        throwInvalidArgument( "'size' is invalid" );

    if( offset > _description.bufferSize )
        throwInvalidArgument( "'offset' is invalid" );

    if( offset + size > _description.bufferSize )
        throwInvalidArgument( "'offset' and 'size' are invalid" );

    void *data = nullptr;

    DWORD flags = 0;

    if( _description.resourceType == ResourceTypeDynamic && offset == 0 && size == _description.bufferSize )
        flags = D3DLOCK_DISCARD;

    const HRESULT lockResult = _buffer->Lock( offset, size, &data, flags );
    checkResult( lockResult, "IDirect3DVertexBuffer9::Lock" );

    std::memcpy( data, vertices, size );

    const HRESULT unlockResult = _buffer->Unlock();
    checkResult( unlockResult, "IDirect3DVertexBuffer9::Unlock" );

    return;
}

const VertexBuffer::Description& VertexBufferDx9::getDescription() const noexcept {
    return _description;
}

ComPointer< IDirect3DVertexBuffer9 > VertexBufferDx9::getBuffer() const noexcept {
    return _buffer;
}

ComPointer< IDirect3DVertexDeclaration9 > VertexBufferDx9::getVertexDeclaration() const noexcept {
    return _vertexDeclaration;
}

std::shared_ptr< VertexBuffer > VertexBuffer::create(
    const Description &description, const void *vertices )
{
    return std::make_shared< VertexBufferDx9 >( description, vertices );
}

}