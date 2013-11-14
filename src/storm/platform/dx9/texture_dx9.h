#pragma once

#include <storm/noncopyable.h>
#include <storm/platform/dx9/core_types_dx9.h>
#include <storm/platform/win/com_pointer.h>
#include <storm/texture.h>

struct IDirect3DTexture9;

namespace storm {

class TextureDx9 : public Texture {
    NONCOPYABLE( TextureDx9 );
public:
    TextureDx9( const Description&, const void *texels = nullptr );

    virtual void getTexels( unsigned int lodIndex, void *texels ) const;
    virtual void setTexels( unsigned int lodIndex, const void *texels );

    virtual const Description& getDescription() const noexcept;

    ComPointer< IDirect3DTexture9 > getTexture() const noexcept;

private:
    size_t getTexelSize() const;

    static D3DFORMAT convertFormat( Format );

    Description _description;
    ComPointer< IDirect3DTexture9 > _texture;
};

}
