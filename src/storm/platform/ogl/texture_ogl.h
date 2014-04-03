#pragma once

#include <storm/platform/ogl/handle_ogl.h>
#include <storm/texture.h>

namespace storm {

class TextureHandleOgl : public HandleOgl {
public:
    TextureHandleOgl();
    ~TextureHandleOgl();
};

class TextureOgl : public Texture {
    NONCOPYABLE( TextureOgl );
public:
    TextureOgl( const Description&, const void *texels = nullptr );

    virtual void getTexels( unsigned int mipLevel, void *texels ) const;
    virtual void setTexels( const Region &region, const void *texels );

    virtual void generateMipMap();

    virtual const Description& getDescription() const;

    const TextureHandleOgl& getHandle() const;

    GLenum getTarget() const;

private:
    static void validateDescription( const Description& );

    static GLenum selectTarget( Layout );

    struct TexelDescription {
        GLenum internalFormat;
        GLenum format;
        GLenum type;
    };

    static TexelDescription selectTexelDescription( Format );

    static unsigned int getMipLevelsMaximum( const Description& );

    Description _description;
    TexelDescription _texelDescription;
    TextureHandleOgl _texture;
    GLenum _target;
};

}
