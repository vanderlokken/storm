#include <storm/ogl/texture_storage_ogl.h>

#include <algorithm>

#include <storm/throw_exception.h>

//  EXT_texture_compression_s3tc extension
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT  0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3

// EXT_texture_sRGB
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT  0x8C4C
#define GL_COMPRESSED_SRGBA_S3TC_DXT1_EXT 0x8C4D
#define GL_COMPRESSED_SRGBA_S3TC_DXT3_EXT 0x8C4E
#define GL_COMPRESSED_SRGBA_S3TC_DXT5_EXT 0x8C4F

namespace storm {

namespace {

// glTexImage*D functions require pixel format and pixel type even when no
// pixel data is specified.

struct PixelDescription {
    GLenum format;
    GLenum type;
};

PixelDescription getCompatiblePixelDescription( GLenum internalFormat ) {
    switch( internalFormat ) {
    case GL_R8:
        return {GL_RED, GL_UNSIGNED_BYTE};
    case GL_R8_SNORM:
        return {GL_RED, GL_BYTE};
    case GL_R16:
        return {GL_RED, GL_UNSIGNED_SHORT};
    case GL_R16_SNORM:
        return {GL_RED, GL_SHORT};
    case GL_RG8:
        return {GL_RG, GL_UNSIGNED_BYTE};
    case GL_RG8_SNORM:
        return {GL_RG, GL_BYTE};
    case GL_RG16:
        return {GL_RG, GL_UNSIGNED_SHORT};
    case GL_RG16_SNORM:
        return {GL_RG, GL_SHORT};
    case GL_R3_G3_B2:
        return {GL_RGB, GL_UNSIGNED_BYTE_3_3_2};
    case GL_RGB4:
        return {GL_RGB, GL_UNSIGNED_SHORT_5_6_5};
    case GL_RGB5:
        return {GL_RGB, GL_UNSIGNED_SHORT_5_6_5};
    case GL_RGB8:
        return {GL_RGB, GL_UNSIGNED_BYTE};
    case GL_RGB8_SNORM:
        return {GL_RGB, GL_BYTE};
    case GL_RGB10:
        return {GL_RGB, GL_UNSIGNED_SHORT};
    case GL_RGB12:
        return {GL_RGB, GL_UNSIGNED_SHORT};
    case GL_RGB16_SNORM:
        return {GL_RGB, GL_SHORT};
    case GL_RGBA2:
        return {GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4};
    case GL_RGBA4:
        return {GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4};
    case GL_RGB5_A1:
        return {GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1};
    case GL_RGBA8:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_RGBA8_SNORM:
        return {GL_RGBA, GL_BYTE};
    case GL_RGB10_A2:
        return {GL_RGBA, GL_UNSIGNED_INT_10_10_10_2};
    case GL_RGB10_A2UI:
        return {GL_RGBA_INTEGER, GL_UNSIGNED_INT_10_10_10_2};
    case GL_RGBA12:
        return {GL_RGBA, GL_UNSIGNED_SHORT};
    case GL_RGBA16:
        return {GL_RGBA, GL_UNSIGNED_SHORT};
    case GL_SRGB8:
        return {GL_RGB, GL_UNSIGNED_BYTE};
    case GL_SRGB8_ALPHA8:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_R16F:
        return {GL_RED, GL_HALF_FLOAT};
    case GL_RG16F:
        return {GL_RG, GL_HALF_FLOAT};
    case GL_RGB16F:
        return {GL_RGB, GL_HALF_FLOAT};
    case GL_RGBA16F:
        return {GL_RGBA, GL_HALF_FLOAT};
    case GL_R32F:
        return {GL_RED, GL_FLOAT};
    case GL_RG32F:
        return {GL_RG, GL_FLOAT};
    case GL_RGB32F:
        return {GL_RGB, GL_FLOAT};
    case GL_RGBA32F:
        return {GL_RGBA, GL_FLOAT};
    case GL_R11F_G11F_B10F:
        return {GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV};
    case GL_RGB9_E5:
        return {GL_RGB, GL_UNSIGNED_INT_5_9_9_9_REV};
    case GL_R8I:
        return {GL_RED_INTEGER, GL_BYTE};
    case GL_R8UI:
        return {GL_RED_INTEGER, GL_UNSIGNED_BYTE};
    case GL_R16I:
        return {GL_RED_INTEGER, GL_SHORT};
    case GL_R16UI:
        return {GL_RED_INTEGER, GL_UNSIGNED_SHORT};
    case GL_R32I:
        return {GL_RED_INTEGER, GL_INT};
    case GL_R32UI:
        return {GL_RED_INTEGER, GL_UNSIGNED_INT};
    case GL_RG8I:
        return {GL_RG_INTEGER, GL_BYTE};
    case GL_RG8UI:
        return {GL_RG_INTEGER, GL_UNSIGNED_BYTE};
    case GL_RG16I:
        return {GL_RG_INTEGER, GL_SHORT};
    case GL_RG16UI:
        return {GL_RG_INTEGER, GL_UNSIGNED_SHORT};
    case GL_RG32I:
        return {GL_RG_INTEGER, GL_INT};
    case GL_RG32UI:
        return {GL_RG_INTEGER, GL_UNSIGNED_INT};
    case GL_RGB8I:
        return {GL_RGB_INTEGER, GL_BYTE};
    case GL_RGB8UI:
        return {GL_RGB_INTEGER, GL_UNSIGNED_BYTE};
    case GL_RGB16I:
        return {GL_RGB_INTEGER, GL_SHORT};
    case GL_RGB16UI:
        return {GL_RGB_INTEGER, GL_UNSIGNED_SHORT};
    case GL_RGB32I:
        return {GL_RGB_INTEGER, GL_INT};
    case GL_RGB32UI:
        return {GL_RGB_INTEGER, GL_UNSIGNED_INT};
    case GL_RGBA8I:
        return {GL_RGBA_INTEGER, GL_BYTE};
    case GL_RGBA8UI:
        return {GL_RGBA_INTEGER, GL_UNSIGNED_BYTE};
    case GL_RGBA16I:
        return {GL_RGBA_INTEGER, GL_SHORT};
    case GL_RGBA16UI:
        return {GL_RGBA_INTEGER, GL_UNSIGNED_SHORT};
    case GL_RGBA32I:
        return {GL_RGBA_INTEGER, GL_INT};
    case GL_RGBA32UI:
        return {GL_RGBA_INTEGER, GL_UNSIGNED_INT};
    case GL_DEPTH_COMPONENT16:
        return {GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT};
    case GL_DEPTH_COMPONENT24:
        return {GL_DEPTH_COMPONENT, GL_UNSIGNED_INT};
    case GL_DEPTH_COMPONENT32:
        return {GL_DEPTH_COMPONENT, GL_UNSIGNED_INT};
    case GL_DEPTH_COMPONENT32F:
        return {GL_DEPTH_COMPONENT, GL_FLOAT};
    case GL_DEPTH24_STENCIL8:
        return {GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8};
    case GL_DEPTH32F_STENCIL8:
        return {GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV};
    case GL_STENCIL_INDEX8:
        return {GL_STENCIL_INDEX, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
        return {GL_RGB, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
        return {GL_RGB, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_SRGBA_S3TC_DXT1_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_SRGBA_S3TC_DXT3_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    case GL_COMPRESSED_SRGBA_S3TC_DXT5_EXT:
        return {GL_RGBA, GL_UNSIGNED_BYTE};
    default:
        storm_assert_unreachable( "Unsupported internal format value" );
    }

    return {0, 0};
}

// TODO: support compressed texture formats
// GL_COMPRESSED_RED
// GL_COMPRESSED_RG
// GL_COMPRESSED_RGB
// GL_COMPRESSED_RGBA
// GL_COMPRESSED_SRGB
// GL_COMPRESSED_SRGB_ALPHA
// GL_COMPRESSED_RED_RGTC1
// GL_COMPRESSED_SIGNED_RED_RGTC1
// GL_COMPRESSED_RG_RGTC2
// GL_COMPRESSED_SIGNED_RG_RGTC2
// GL_COMPRESSED_RGBA_BPTC_UNORM
// GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM
// GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT
// GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT

}

void glTexStorage1D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width )
{
    if( gpuContext.isFunctionAvailable<GlTexStorage1D>() ) {
        gpuContext.call<GlTexStorage1D>(
            target,
            levels,
            internalFormat,
            width );
        return;
    }

    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        gpuContext.call<GlTexImage1D>(
            target,
            level,
            internalFormat,
            width,
            0,
            pixelDescription.format,
            pixelDescription.type,
            nullptr );

        width = std::max( 1, (width / 2) );
    }
}

void glTexStorage2D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height )
{
    if( gpuContext.isFunctionAvailable<GlTexStorage2D>() ) {
        gpuContext.call<GlTexStorage2D>(
            target,
            levels,
            internalFormat,
            width,
            height );
        return;
    }

    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        if( target != GL_TEXTURE_CUBE_MAP ) {
            gpuContext.call<GlTexImage2D>(
                target,
                level,
                internalFormat,
                width,
                height,
                0,
                pixelDescription.format,
                pixelDescription.type,
                nullptr );
        } else {
            const GLenum faces[] = {
                GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
            };
            for( GLenum face : faces ) {
                gpuContext.call<GlTexImage2D>(
                    face,
                    level,
                    internalFormat,
                    width,
                    height,
                    0,
                    pixelDescription.format,
                    pixelDescription.type,
                    nullptr );
            }
        }

        width = std::max( 1, (width / 2) );

        if( target != GL_TEXTURE_1D_ARRAY ) {
            height = std::max( 1, (height / 2) );
        }
    }
}

void glTexStorage3D(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei levels,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth )
{
    if( gpuContext.isFunctionAvailable<GlTexStorage3D>() ) {
        gpuContext.call<GlTexStorage3D>(
            target,
            levels,
            internalFormat,
            width,
            height,
            depth );
        return;
    }

    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        gpuContext.call<GlTexImage3D>(
            target,
            level,
            internalFormat,
            width,
            height,
            depth,
            0,
            pixelDescription.format,
            pixelDescription.type,
            nullptr );

        width = std::max( 1, (width / 2) );
        height = std::max( 1, (height / 2) );

        if( target != GL_TEXTURE_2D_ARRAY ) {
            depth = std::max( 1, (depth / 2) );
        }
    }
}

void glTexStorage2DMultisample(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLboolean fixedSampleLocations )
{
    if( gpuContext.isFunctionAvailable<GlTexStorage2DMultisample>() ) {
        gpuContext.call<GlTexStorage2DMultisample>(
            target,
            samples,
            internalFormat,
            width,
            height,
            fixedSampleLocations );
    } else {
        gpuContext.call<GlTexImage2DMultisample>(
            target,
            samples,
            internalFormat,
            width,
            height,
            fixedSampleLocations );
    }
}

void glTexStorage3DMultisample(
    const GpuContextOgl &gpuContext,
    GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLboolean fixedSampleLocations )
{
    if( gpuContext.isFunctionAvailable<GlTexStorage3DMultisample>() ) {
        gpuContext.call<GlTexStorage3DMultisample>(
            target,
            samples,
            internalFormat,
            width,
            height,
            depth,
            fixedSampleLocations );
    } else {
        gpuContext.call<GlTexImage3DMultisample>(
            target,
            samples,
            internalFormat,
            width,
            height,
            depth,
            fixedSampleLocations );
    }
}

}
