#include <storm/platform/ogl/texture_storage_ogl.h>

#include <algorithm>
#include <map>

#include <storm/platform/ogl/check_result_ogl.h>

namespace storm {

namespace {

// glTexImage*D functions require pixel format and pixel type even when no
// pixel data is specified.

struct PixelDescription {
    GLenum format;
    GLenum type;
};

PixelDescription getCompatiblePixelDescription( GLenum internalFormat ) {
    static const std::map<GLenum, PixelDescription> mapping = {
        {GL_R8, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_R8_SNORM, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_R16, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_R16_SNORM, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_RG8, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_RG8_SNORM, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_RG16, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_RG16_SNORM, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_R3_G3_B2, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB4, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB5, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB8, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB8_SNORM, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB10, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB12, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB16_SNORM, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGBA2, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGBA4, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_RGB5_A1, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGBA8, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGBA8_SNORM, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGB10_A2, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGB10_A2UI, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGBA12, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_RGBA16, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_SRGB8, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_SRGB8_ALPHA8, {GL_RGBA, GL_UNSIGNED_BYTE}},

        {GL_R16F, {GL_RED, GL_FLOAT}},
        {GL_RG16F, {GL_RG, GL_FLOAT}},
        {GL_RGB16F, {GL_RGB, GL_FLOAT}},
        {GL_RGBA16F, {GL_RGBA, GL_FLOAT}},
        {GL_R32F, {GL_RED, GL_FLOAT}},
        {GL_RG32F, {GL_RG, GL_FLOAT}},
        {GL_RGB32F, {GL_RGB, GL_FLOAT}},
        {GL_RGBA32F, {GL_RGBA, GL_FLOAT}},
        {GL_R11F_G11F_B10F, {GL_RGB, GL_FLOAT}},
        {GL_RGB9_E5, {GL_RGB, GL_FLOAT}},

        {GL_R8I, {GL_RED_INTEGER, GL_INT}},
        {GL_R8UI, {GL_RED_INTEGER, GL_UNSIGNED_INT}},
        {GL_R16I, {GL_RED_INTEGER, GL_INT}},
        {GL_R16UI, {GL_RED_INTEGER, GL_UNSIGNED_INT}},
        {GL_R32I, {GL_RED_INTEGER, GL_INT}},
        {GL_R32UI, {GL_RED_INTEGER, GL_UNSIGNED_INT}},
        {GL_RG8I, {GL_RG_INTEGER, GL_INT}},
        {GL_RG8UI, {GL_RG_INTEGER, GL_UNSIGNED_INT}},
        {GL_RG16I, {GL_RG_INTEGER, GL_INT}},
        {GL_RG16UI, {GL_RG_INTEGER, GL_UNSIGNED_INT}},
        {GL_RG32I, {GL_RG_INTEGER, GL_INT}},
        {GL_RG32UI, {GL_RG_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGB8I, {GL_RGB_INTEGER, GL_INT}},
        {GL_RGB8UI, {GL_RGB_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGB16I, {GL_RGB_INTEGER, GL_INT}},
        {GL_RGB16UI, {GL_RGB_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGB32I, {GL_RGB_INTEGER, GL_INT}},
        {GL_RGB32UI, {GL_RGB_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGBA8I, {GL_RGBA_INTEGER, GL_INT}},
        {GL_RGBA8UI, {GL_RGBA_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGBA16I, {GL_RGBA_INTEGER, GL_INT}},
        {GL_RGBA16UI, {GL_RGBA_INTEGER, GL_UNSIGNED_INT}},
        {GL_RGBA32I, {GL_RGBA_INTEGER, GL_INT}},
        {GL_RGBA32UI, {GL_RGBA_INTEGER, GL_UNSIGNED_INT}},

        {GL_DEPTH_COMPONENT16, {GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}},
        {GL_DEPTH_COMPONENT24, {GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}},
        {GL_DEPTH_COMPONENT32, {GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}},
        {GL_DEPTH_COMPONENT32F, {GL_DEPTH_COMPONENT, GL_FLOAT}},
        {GL_DEPTH24_STENCIL8, {GL_DEPTH_STENCIL, GL_UNSIGNED_INT}},
        {GL_DEPTH32F_STENCIL8, {GL_DEPTH_STENCIL, GL_FLOAT}},
        {GL_STENCIL_INDEX8, {GL_STENCIL_INDEX, GL_UNSIGNED_INT}},

        {GL_COMPRESSED_RED, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RG, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RGB, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RGBA, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_SRGB, {GL_RGB, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_SRGB_ALPHA, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RED_RGTC1, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_SIGNED_RED_RGTC1, {GL_RED, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RG_RGTC2, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_SIGNED_RG_RGTC2, {GL_RG, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RGBA_BPTC_UNORM, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, {GL_RGBA, GL_UNSIGNED_BYTE}},
        {GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, {GL_RGB, GL_FLOAT}},
        {GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT, {GL_RGB, GL_FLOAT}},
        // {GL_COMPRESSED_RGB_S3TC_DXT1_EXT, {GL_RGB, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_SRGB_S3TC_DXT1_EXT, {GL_RGB, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}},
        // {GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, {GL_RGBA, GL_UNSIGNED_BYTE}}
    };
    storm_assert( mapping.count(internalFormat) );
    return mapping.at( internalFormat );
}

}

void APIENTRY glTexStorage1D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width )
{
    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        ::glTexImage1D( target, level, internalFormat, width, 0,
            pixelDescription.format, pixelDescription.type, nullptr );
        checkResult( "::glTexImage1D" );

        width = std::max( 1, (width / 2) );
    }
}

void APIENTRY glTexStorage2D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width, GLsizei height )
{
    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        ::glTexImage2D( target, level, internalFormat, width, height, 0,
            pixelDescription.format, pixelDescription.type, nullptr );
        checkResult( "::glTexImage2D" );

        width = std::max( 1, (width / 2) );
        if( target != GL_TEXTURE_1D_ARRAY )
            height = std::max( 1, (height / 2) );
    }
}

void APIENTRY glTexStorage3D( GLenum target, GLsizei levels,
    GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth )
{
    for( GLsizei level = 0; level < levels; ++level ) {
        const PixelDescription pixelDescription =
            getCompatiblePixelDescription( internalFormat );

        ::glTexImage3D( target, level, internalFormat, width, height, depth, 0,
            pixelDescription.format, pixelDescription.type, nullptr );
        checkResult( "::glTexImage3D" );

        width = std::max( 1, (width / 2) );
        height = std::max( 1, (height / 2) );
        if( target != GL_TEXTURE_2D_ARRAY )
            depth = std::max( 1, (depth / 2) );
    }
}

void APIENTRY glTexStorage2DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLboolean fixedSampleLocations )
{
    ::glTexImage2DMultisample(
        target, samples, internalFormat, width, height, fixedSampleLocations );
}

void APIENTRY glTexStorage3DMultisample( GLenum target,
    GLsizei samples,
    GLenum internalFormat,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLboolean fixedSampleLocations )
{
    ::glTexStorage3DMultisample( target, samples, internalFormat,
        width, height, depth, fixedSampleLocations );
}

}
