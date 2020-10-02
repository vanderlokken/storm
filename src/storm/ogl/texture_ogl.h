#pragma once

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>
#include <storm/texture.h>

namespace storm {

using TextureHandleOgl = HandleOgl<GlGenTextures, GlDeleteTextures>;

class TextureOgl : public Texture {
public:
    TextureOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description );

    void getTexels(
        unsigned int mipLevel, size_t size, void *texels ) const override;

    void setTexels(
        const Separate1dRegion &region, const void *texels ) override;
    void setTexels(
        const Separate2dRegion &region, const void *texels ) override;
    void setTexels(
        const Separate3dRegion &region, const void *texels ) override;
    void setTexels(
        const Layered1dRegion &region, const void *texels ) override;
    void setTexels(
        const Layered2dRegion &region, const void *texels ) override;
    void setTexels(
        const CubeMapRegion &region, const void *texels ) override;

    void generateMipMap() override;

    const Description& getDescription() const override;

    const TextureHandleOgl& getHandle() const;

    GLenum getTarget() const;

    static GLenum convertCubeMapFace( unsigned int face );

private:
    void validateDescription() const;

    void setTexelTransferAlignment(
        const GpuContextOgl &gpuContext, unsigned int width ) const;
    void resetTexelTransferAlignment(
        const GpuContextOgl &gpuContext ) const;

    struct CompressedRegion {
        GLenum target;
        unsigned int mipLevel;
        unsigned int x;
        unsigned int y;
        unsigned int z;
        unsigned int width;
        unsigned int height;
        unsigned int depth;
    };

    void setTexelsCompressed(
        const GpuContextOgl &gpuContext,
        const CompressedRegion &region,
        const void *texels );

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
