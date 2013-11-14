#include <storm/platform/dx9/index_buffer_dx9.h>

#include <d3d9.h>

#include <storm/platform/dx9/rendering_system_dx9.h>
#include <storm/platform/dx9/resource_type_dx9.h>
#include <storm/platform/win/check_result.h>

namespace storm {

IndexBufferDx9::IndexBufferDx9( const Description &description, const void *indices )
    : _description( description )
{
    ComPointer< IDirect3DDevice9 > device = RenderingSystemDx9::getDevice();

    const UINT size = description.bufferSize;
    const DWORD usage = selectResourceUsage( description.resourceType );
    const D3DPOOL pool = selectResourcePool( description.resourceType );
    const D3DFORMAT format = selectFormat( description.indexSize );

    const HRESULT result = device->CreateIndexBuffer(
        size, usage, format, pool, _buffer.getAddress(), nullptr );

    checkResult( result, "IDirect3DDevice9::CreateIndexBuffer" );

    if( indices ) {
        setIndices( 0, description.bufferSize, indices );
    }
    return;
}

void IndexBufferDx9::getIndices( size_t offset, size_t size, void *indices ) const {

    if( size > _description.bufferSize )
        throwInvalidArgument( "'size' is invalid" );

    if( offset > _description.bufferSize )
        throwInvalidArgument( "'offset' is invalid" );

    if( offset + size > _description.bufferSize )
        throwInvalidArgument( "'offset' and 'size' are invalid" );

    void *data = nullptr;

    const HRESULT lockResult = _buffer->Lock( offset, size, &data, D3DLOCK_READONLY );
    checkResult( lockResult, "IDirect3DIndexBuffer9::Lock" );

    std::memcpy( indices, data, size );

    const HRESULT unlockResult = _buffer->Unlock();
    checkResult( unlockResult, "IDirect3DIndexBuffer9::Unlock" );

    return;
}

void IndexBufferDx9::setIndices( size_t offset, size_t size, const void *indices ) {

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
    checkResult( lockResult, "IDirect3DIndexBuffer9::Lock" );

    std::memcpy( data, indices, size );

    const HRESULT unlockResult = _buffer->Unlock();
    checkResult( unlockResult, "IDirect3DIndexBuffer9::Unlock" );

    return;
}

const IndexBuffer::Description& IndexBufferDx9::getDescription() const noexcept {
    return _description;
}

ComPointer< IDirect3DIndexBuffer9 > IndexBufferDx9::getBuffer() const noexcept {
    return _buffer;
}

D3DFORMAT IndexBufferDx9::selectFormat( size_t indexSize ) {
    D3DFORMAT result;

    switch( indexSize ) {
    case 2:
        result = D3DFMT_INDEX16;
        break;

    case 4:
        result = D3DFMT_INDEX32;
        break;

    default:
        throwInvalidArgument( "'indexSize' is invalid" );
    }
    return result;
}

std::shared_ptr< IndexBuffer > IndexBuffer::create(
    const Description &description, const void *indices )
{
    return std::make_shared< IndexBufferDx9 >( description, indices );
}

}