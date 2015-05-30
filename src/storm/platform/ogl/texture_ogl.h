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
    TextureOgl( const Description& );

    virtual void getTexels(
        unsigned int mipLevel, unsigned int size, void *texels ) const;

    virtual void setTexels(
        const Separate1dRegion &region, const void *texels );
    virtual void setTexels(
        const Separate2dRegion &region, const void *texels );
    virtual void setTexels(
        const Separate3dRegion &region, const void *texels );
    virtual void setTexels(
        const Layered1dRegion &region, const void *texels );
    virtual void setTexels(
        const Layered2dRegion &region, const void *texels );
    virtual void setTexels(
        const CubeMapRegion &region, const void *texels );

    virtual void generateMipMap();

    virtual const Description& getDescription() const;

    const TextureHandleOgl& getHandle() const;

    GLenum getTarget() const;

    static GLenum convertCubeMapFace( unsigned int face );

private:
    void validateDescription() const;

    void setTexelTransferAlignment( unsigned int width ) const;
    void resetTexelTransferAlignment() const;

    struct CompressedRegion {
        GLenum target;
        unsigned int mipLevel;
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
    };

    void setTexelsCompressed(
        const CompressedRegion &region, const void *texels );

    static GLenum selectTarget( Layout );

    struct TexelDescription {
        GLenum internalFormat;
        GLenum format;
        GLenum type;
        unsigned int size;
        bool compressed;
    };

    static TexelDescription selectTexelDescription( Format );

    static unsigned int getMipLevelsMaximum( const Description& );

    Description _description;
    TexelDescription _texelDescription;
    TextureHandleOgl _texture;
    GLenum _target;
};

}
