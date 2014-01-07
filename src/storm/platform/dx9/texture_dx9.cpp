#include <storm/platform/dx9/texture_dx9.h>

#include <d3d9.h>

#include <storm/platform/dx9/rendering_system_dx9.h>
#include <storm/platform/dx9/resource_type_dx9.h>
#include <storm/platform/win/check_result.h>

namespace storm {

TextureDx9::TextureDx9( const Description &description, const void *texels )
    : _description( description )
{
    ComPointer< IDirect3DDevice9 > device = RenderingSystemDx9::getDevice();

    const UINT width = _description.dimensions.getWidth();
    const UINT height = _description.dimensions.getHeight();
    const UINT levelCount = (_description.lodGenerationMode == LodGenerationMode::Custom) ? _description.customLodCount : 0;
          DWORD usage = selectResourceUsage( _description.resourceType );
    const D3DPOOL pool = selectResourcePool( _description.resourceType );
    const D3DFORMAT format = convertFormat( _description.format );

    usage |= _description.lodGenerationMode == LodGenerationMode::Automatic ? D3DUSAGE_AUTOGENMIPMAP : 0;

    const HRESULT result = device->CreateTexture(
        width, height, levelCount, usage, format, pool, _texture.getAddress(), nullptr );

    checkResult( result, "IDirect3DDevice9::CreateTexture" );

    if( texels ) {
        setTexels( 0, texels );
    }
    return;
}

void TextureDx9::getTexels( unsigned int lodIndex, void *texels ) const {
    throwRuntimeError( "Not implemented" );
}

void TextureDx9::setTexels( unsigned int lodIndex, const void *texels ) {
    D3DLOCKED_RECT lockedRectangle;

    const HRESULT lockResult = _texture->LockRect( lodIndex, &lockedRectangle, nullptr, 0 );
    checkResult( lockResult, "IDirect3DTexture9::LockRect" );

    const size_t width = _description.dimensions.getWidth();
    const size_t height = _description.dimensions.getHeight();

    const size_t rowSize = getTexelSize() * width;

    if( lockedRectangle.Pitch == rowSize ) {
        ::memcpy( lockedRectangle.pBits, texels, rowSize * height );
    } else {
        char *begin = static_cast<char*>( lockedRectangle.pBits );
        char *end = begin + lockedRectangle.Pitch * height;

        for( char *row = begin; row != end; row += lockedRectangle.Pitch ) {
            ::memcpy( row, texels, rowSize );
            texels = static_cast<const char*>( texels ) + rowSize;
        }
    }

    const HRESULT unlockResult = _texture->UnlockRect( lodIndex );
    checkResult( unlockResult, "IDirect3DTexture9::UnlockRect" );
    return;
}

const Texture::Description& TextureDx9::getDescription() const noexcept {
    return _description;
}

ComPointer< IDirect3DTexture9 > TextureDx9::getTexture() const noexcept {
    return _texture;
}

size_t TextureDx9::getTexelSize() const {
    switch( _description.format ) {
    case Format::RgbUint8:
        return 3;
    case Format::ArgbUint8:
        return 4;
    default:
        throwInvalidArgument( "'format' is invalid" );
    }
}

D3DFORMAT TextureDx9::convertFormat( Format format ) {
    switch( format ) {
    case Format::RgbUint8:
        return D3DFMT_R8G8B8;
    case Format::ArgbUint8:
        return D3DFMT_A8R8G8B8;
    default:
        throwInvalidArgument( "'format' is invalid" );
    }
}

}