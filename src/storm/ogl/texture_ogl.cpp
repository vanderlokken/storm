#include <storm/ogl/texture_ogl.h>

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <map>

#include <storm/ogl/texture_storage_ogl.h>
#include <storm/throw_exception.h>

// EXT_texture_compression_s3tc extension
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

class ScopeTextureBinding {
public:
    ScopeTextureBinding(
            const GpuContextOgl &gpuContext, GLenum target, GLuint binding ) :
        _gpuContext( gpuContext ),
        _target( target )
    {
        GLenum bindingEnumeration = 0;
        switch( _target ) {
        case GL_TEXTURE_1D:
            bindingEnumeration = GL_TEXTURE_BINDING_1D;
            break;
        case GL_TEXTURE_2D:
            bindingEnumeration = GL_TEXTURE_BINDING_2D;
            break;
        case GL_TEXTURE_2D_MULTISAMPLE:
            bindingEnumeration = GL_TEXTURE_BINDING_2D_MULTISAMPLE;
            break;
        case GL_TEXTURE_3D:
            bindingEnumeration = GL_TEXTURE_BINDING_3D;
            break;
        case GL_TEXTURE_1D_ARRAY:
            bindingEnumeration = GL_TEXTURE_BINDING_1D_ARRAY;
            break;
        case GL_TEXTURE_2D_ARRAY:
            bindingEnumeration = GL_TEXTURE_BINDING_2D_ARRAY;
            break;
        case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
            bindingEnumeration = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
            break;
        case GL_TEXTURE_CUBE_MAP:
            bindingEnumeration = GL_TEXTURE_BINDING_CUBE_MAP;
            break;
        case GL_TEXTURE_BUFFER:
            bindingEnumeration = GL_TEXTURE_BINDING_BUFFER;
            break;
        default:
            storm_assert_unreachable( "Unexpected target value" );
        }

        _gpuContext.call<GlGetIntegerv>(
            bindingEnumeration, &_previousBinding );
        _gpuContext.call<GlBindTexture>(
            target, binding );
    }

    ~ScopeTextureBinding() {
        _gpuContext.callUnchecked<GlBindTexture>( _target, _previousBinding );
    }

private:
    const GpuContextOgl &_gpuContext;
    GLenum _target;
    GLint _previousBinding;
};

TextureOgl::TextureOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description ) :
    _description( description ),
    _texelDescription( selectTexelDescription(description.format) ),
    _texture( gpuContext ),
    _target( selectTarget(description.layout) )
{
    validateDescription();

    const ScopeTextureBinding scopeTextureBinding(
        *gpuContext, _target, _texture );

    const unsigned int levelsMaximum = getMipLevelsMaximum( _description );
    const unsigned int levels = _description.mipLevels == CompleteMipMap ?
        levelsMaximum : _description.mipLevels;
    storm_assert( levels <= levelsMaximum );

    if( _description.mipLevels == CompleteMipMap )
        _description.mipLevels = levels;

    switch( _description.layout ) {
    case Layout::Separate1d:
        glTexStorage1D(
            *gpuContext,
            _target, levels, _texelDescription.internalFormat,
            description.width );
        break;
    case Layout::Separate2d:
    case Layout::CubeMap:
        glTexStorage2D(
            *gpuContext,
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height );
        break;
    case Layout::Separate3d:
        glTexStorage3D(
            *gpuContext,
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height,
            description.depth );
        break;
    case Layout::Layered1d:
        glTexStorage2D(
            *gpuContext,
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.layers );
        break;
    case Layout::Layered2d:
        glTexStorage3D(
            *gpuContext,
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height,
            description.layers );
        break;
    case Layout::Separate2dMsaa:
        glTexStorage2DMultisample(
            *gpuContext,
            _target, description.texelSamples,
            _texelDescription.internalFormat,
            description.width,
            description.height,
            GL_TRUE );
        break;
    case Layout::Layered2dMsaa:
        glTexStorage3DMultisample(
            *gpuContext,
            _target, description.texelSamples,
            _texelDescription.internalFormat,
            description.width,
            description.height,
            description.layers,
            GL_TRUE );
        break;
    default:
        throwNotImplemented();
    }
}

void TextureOgl::getTexels(
    unsigned int mipLevel, size_t /*size*/, void *texels ) const
{
    storm_assert( _description.layout != Layout::Separate2dMsaa );
    storm_assert( _description.layout != Layout::Layered2dMsaa );

    storm_assert( mipLevel < _description.mipLevels );

    // TODO: check size

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    if( _description.layout == Layout::CubeMap ) {

        if( _texelDescription.compressed )
            throwNotImplemented();

        const MipLevelDimensions mipLevelDimensions =
            getMipLevelDimensions( mipLevel );

        setTexelTransferAlignment( gpuContext, mipLevelDimensions.width );

        const GLenum targets[] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };

        for( GLenum target : targets ) {
            gpuContext.call<GlGetTexImage>( target, mipLevel,
                _texelDescription.format, _texelDescription.type, texels );

            texels = static_cast<unsigned char*>( texels ) +
                _texelDescription.size *
                mipLevelDimensions.width *
                mipLevelDimensions.height;
        }

        resetTexelTransferAlignment( gpuContext );
        return;
    }

    if( !_texelDescription.compressed ) {
        setTexelTransferAlignment(
            gpuContext, getMipLevelDimensions(mipLevel).width );

        gpuContext.call<GlGetTexImage>( _target, mipLevel,
            _texelDescription.format, _texelDescription.type, texels );

        resetTexelTransferAlignment( gpuContext );
    } else {
        gpuContext.call<GlGetCompressedTexImage>( _target, mipLevel, texels );
    }
}

void TextureOgl::setTexels(
    const Separate1dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate1d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    gpuContext.call<GlTexSubImage1D>(
        _target,
        region.mipLevel,
        region.x,
        region.width,
        _texelDescription.format, _texelDescription.type, data );
}

void TextureOgl::setTexels(
    const Separate2dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate2d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    if( _texelDescription.compressed ) {
        CompressedRegion compressedRegion;

        compressedRegion.target = _target;
        compressedRegion.mipLevel = region.mipLevel;
        compressedRegion.x = region.x;
        compressedRegion.y = region.y;
        compressedRegion.z = 0;
        compressedRegion.width = region.width;
        compressedRegion.height = region.height;
        compressedRegion.depth = 1;

        setTexelsCompressed( gpuContext, compressedRegion, data );
        return;
    }

    setTexelTransferAlignment( gpuContext, region.width );

    gpuContext.call<GlTexSubImage2D>(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.width,
        region.height,
        _texelDescription.format, _texelDescription.type, data );

    resetTexelTransferAlignment( gpuContext );
}

void TextureOgl::setTexels(
    const Separate3dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate3d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );
    storm_assert( region.z + region.depth <= mipLevelDimensions.depth );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    setTexelTransferAlignment( gpuContext, region.width );

    gpuContext.call<GlTexSubImage3D>(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.z,
        region.width,
        region.height,
        region.depth,
        _texelDescription.format, _texelDescription.type, data );

    resetTexelTransferAlignment( gpuContext );
}

void TextureOgl::setTexels(
    const Layered1dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Layered1d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.layer < _description.layers );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    gpuContext.call<GlTexSubImage2D>(
        _target,
        region.mipLevel,
        region.x,
        region.layer,
        region.width,
        /* depth = */ 1,
        _texelDescription.format, _texelDescription.type, data );
}

void TextureOgl::setTexels(
    const Layered2dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Layered2d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.layer < _description.layers );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    if( _texelDescription.compressed ) {
        CompressedRegion compressedRegion;

        compressedRegion.target = _target;
        compressedRegion.mipLevel = region.mipLevel;
        compressedRegion.x = region.x;
        compressedRegion.y = region.y;
        compressedRegion.z = region.layer;
        compressedRegion.width = region.width;
        compressedRegion.height = region.height;
        compressedRegion.depth = 1;

        setTexelsCompressed( gpuContext, compressedRegion, data );
        return;
    }

    setTexelTransferAlignment( gpuContext, region.width );

    gpuContext.call<GlTexSubImage3D>(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.layer,
        region.width,
        region.height,
        /* depth = */ 1,
        _texelDescription.format, _texelDescription.type, data );

    resetTexelTransferAlignment( gpuContext );
}

void TextureOgl::setTexels(
    const CubeMapRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::CubeMap );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    if( _texelDescription.compressed ) {
        CompressedRegion compressedRegion;

        compressedRegion.target = convertCubeMapFace( region.face );
        compressedRegion.mipLevel = region.mipLevel;
        compressedRegion.x = region.x;
        compressedRegion.y = region.y;
        compressedRegion.z = 0;
        compressedRegion.width = region.width;
        compressedRegion.height = region.height;
        compressedRegion.depth = 1;

        setTexelsCompressed( gpuContext, compressedRegion, data );
        return;
    }

    setTexelTransferAlignment( gpuContext, region.width );

    gpuContext.call<GlTexSubImage2D>(
        convertCubeMapFace( region.face ),
        region.mipLevel,
        region.x,
        region.y,
        region.width,
        region.height,
        _texelDescription.format, _texelDescription.type, data );

    resetTexelTransferAlignment( gpuContext );
}

void TextureOgl::generateMipMap() {
    storm_assert( _description.layout != Layout::Separate2dMsaa );
    storm_assert( _description.layout != Layout::Layered2dMsaa );

    const GpuContextOgl &gpuContext = *_texture.getGpuContext();

    const ScopeTextureBinding scopeTextureBinding(
        gpuContext, _target, _texture );

    gpuContext.call<GlGenerateMipmap>( _target );
}

const Texture::Description& TextureOgl::getDescription() const {
    return _description;
}

const TextureHandleOgl& TextureOgl::getHandle() const {
    return _texture;
}

GLenum TextureOgl::getTarget() const {
    return _target;
}

GLenum TextureOgl::convertCubeMapFace( unsigned int face ) {
    storm_assert( face >= CubeMapFace::PositiveX );
    storm_assert( face <= CubeMapFace::NegativeZ );

    static const GLenum faces[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    return faces[face];
}

void TextureOgl::validateDescription() const {
    storm_assert( _description.width );
    storm_assert( _description.height );
    storm_assert( _description.depth );
    storm_assert( _description.mipLevels );
    storm_assert( _description.layers );
    storm_assert( _description.texelSamples );

    if( _texelDescription.compressed ) {
        storm_assert(
            _description.layout == Layout::Separate2d ||
            _description.layout == Layout::Layered2d ||
            _description.layout == Layout::CubeMap );
    }
}

void TextureOgl::setTexelTransferAlignment(
    const GpuContextOgl &gpuContext, unsigned int width ) const
{
    const std::initializer_list<unsigned int> alignments = {4, 2, 1};

    auto isSuitable = [=]( unsigned int alignment ) {
        return (_texelDescription.size * width) % alignment == 0;
    };

    const unsigned int *alignment = std::find_if(
        alignments.begin(),
        alignments.end(),
        isSuitable );

    gpuContext.call<GlPixelStorei>( GL_PACK_ALIGNMENT, *alignment );
    gpuContext.call<GlPixelStorei>( GL_UNPACK_ALIGNMENT, *alignment );
}

void TextureOgl::resetTexelTransferAlignment(
    const GpuContextOgl &gpuContext ) const
{
    gpuContext.call<GlPixelStorei>( GL_PACK_ALIGNMENT, 4 );
    gpuContext.call<GlPixelStorei>( GL_UNPACK_ALIGNMENT, 4 );
}

void TextureOgl::setTexelsCompressed(
    const GpuContextOgl &gpuContext,
    const CompressedRegion &region,
    const void *texels )
{
    struct BlockDescription {
        GLsizei width;
        GLsizei height;
        GLsizei size;
    };

    static const std::map<Format, BlockDescription> formatBlockDescriptions = {
        {Format::RgbDxt1, {4, 4, 8}},
        {Format::RgbaDxt1, {4, 4, 8}},
        {Format::RgbaDxt3, {4, 4, 16}},
        {Format::RgbaDxt5, {4, 4, 16}},
        {Format::SrgbDxt1, {4, 4, 8}},
        {Format::SrgbaDxt1, {4, 4, 8}},
        {Format::SrgbaDxt3, {4, 4, 16}},
        {Format::SrgbaDxt5, {4, 4, 16}}
    };

    const BlockDescription &block =
        formatBlockDescriptions.at( _description.format );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );
    (void)mipLevelDimensions;

    storm_assert( (region.x % block.width) == 0 );
    storm_assert( (region.y % block.height) == 0 );
    storm_assert( (region.width % block.width) == 0 ||
        region.x + region.width == mipLevelDimensions.width );
    storm_assert( (region.height % block.height) == 0 ||
        region.y + region.height == mipLevelDimensions.height );

    const GLsizei dataSize =
        static_cast<GLsizei>( ceil(1.0f * region.width / block.width) ) *
        static_cast<GLsizei>( ceil(1.0f * region.height / block.height) ) *
        static_cast<GLsizei>( region.depth ) * block.size;

    if( region.target != GL_TEXTURE_2D_ARRAY ) {
        gpuContext.call<GlCompressedTexSubImage2D>(
            region.target,
            region.mipLevel,
            region.x,
            region.y,
            region.width,
            region.height,
            _texelDescription.internalFormat,
            dataSize,
            texels );
    } else {
        gpuContext.call<GlCompressedTexSubImage3D>(
            region.target,
            region.mipLevel,
            region.x,
            region.y,
            region.z,
            region.width,
            region.height,
            region.depth,
            _texelDescription.internalFormat,
            dataSize,
            texels );
    }
}

GLenum TextureOgl::selectTarget( Layout layout ) {
    switch( layout ) {
    case Layout::Separate1d:
        return GL_TEXTURE_1D;
    case Layout::Separate2d:
        return GL_TEXTURE_2D;
    case Layout::Separate3d:
        return GL_TEXTURE_3D;
    case Layout::Layered1d:
        return GL_TEXTURE_1D_ARRAY;
    case Layout::Layered2d:
        return GL_TEXTURE_2D_ARRAY;
    case Layout::CubeMap:
        return GL_TEXTURE_CUBE_MAP;
    case Layout::Separate2dMsaa:
        return GL_TEXTURE_2D_MULTISAMPLE;
    case Layout::Layered2dMsaa:
        return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    default:
        storm_assert_unreachable( "Unexpected layout value" );
        return 0;
    }
}

TextureOgl::TexelDescription
TextureOgl::selectTexelDescription( Format format ) {
    switch( format ) {
    // 8-bit normalized unsigned integer formats.
    case Format::RgbNormUint8:
        return { GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE, 3, false };
    case Format::RgbaNormUint8:
        return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, false };
    case Format::SrgbNormUint8:
        return { GL_SRGB8_ALPHA8, GL_RGB, GL_UNSIGNED_BYTE, 3, false };
    case Format::SrgbaNormUint8:
        return { GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, false };
    // 16-bit floating point formats.
    case Format::RedFloat16:
        return { GL_R16F, GL_RED, GL_HALF_FLOAT, 2, false };
    case Format::RgFloat16:
        return { GL_RG16F, GL_RG, GL_HALF_FLOAT, 4, false };
    case Format::RgbFloat16:
        return { GL_RGB16F, GL_RGB, GL_HALF_FLOAT, 6, false };
    case Format::RgbaFloat16:
        return { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, 8, false };
    // 16-bit integer formats.
    case Format::RedInt16:
        return { GL_R16I, GL_RED_INTEGER, GL_SHORT, 2, false };
    case Format::RgInt16:
        return { GL_RG16I, GL_RG_INTEGER, GL_SHORT, 4, false };
    case Format::RgbInt16:
        return { GL_RGB16I, GL_RGB_INTEGER, GL_SHORT, 6, false };
    case Format::RgbaInt16:
        return { GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT, 8, false };
    // 16-bit unsigned integer formats.
    case Format::RedUint16:
        return { GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT, 2, false };
    case Format::RgUint16:
        return { GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT, 4, false };
    case Format::RgbUint16:
        return { GL_RGB16UI, GL_RGB_INTEGER, GL_UNSIGNED_SHORT, 6, false };
    case Format::RgbaUint16:
        return { GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT, 8, false };
    // 32-bit floating point formats.
    case Format::RedFloat32:
        return { GL_R32F, GL_RED, GL_FLOAT, 4, false };
    case Format::RgFloat32:
        return { GL_RG32F, GL_RG, GL_FLOAT, 8, false };
    case Format::RgbFloat32:
        return { GL_RGB32F, GL_RGB, GL_FLOAT, 12, false };
    case Format::RgbaFloat32:
        return { GL_RGBA32F, GL_RGBA, GL_FLOAT, 16, false };
    // 32-bit integer formats.
    case Format::RedInt32:
        return { GL_R32I, GL_RED_INTEGER, GL_INT, 4, false };
    case Format::RgInt32:
        return { GL_RG32I, GL_RG_INTEGER, GL_INT, 8, false };
    case Format::RgbInt32:
        return { GL_RGB32I, GL_RGB_INTEGER, GL_INT, 12, false };
    case Format::RgbaInt32:
        return { GL_RGBA32I, GL_RGBA_INTEGER, GL_INT, 16, false };
    // 32-bit unsigned integer formats.
    case Format::RedUint32:
        return { GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, 4, false };
    case Format::RgUint32:
        return { GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT, 8, false };
    case Format::RgbUint32:
        return { GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT, 12, false };
    case Format::RgbaUint32:
        return { GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT, 16, false };
    // Depth texture formats.
    case Format::DepthNormUint16:
        return {
            GL_DEPTH_COMPONENT16,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_SHORT, 2, false
        };
    case Format::DepthNormUint24:
        return {
            GL_DEPTH_COMPONENT24,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_INT, 4, false
        };
    case Format::DepthNormUint32:
        return {
            GL_DEPTH_COMPONENT32,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_INT, 4, false
        };
    case Format::DepthNormUint24StencilUint8:
        return {
            GL_DEPTH24_STENCIL8,
            GL_DEPTH_STENCIL,
            // TODO: check texel size value.
            GL_UNSIGNED_INT_24_8, 8, false
        };
    case Format::DepthFloat32:
        return {
            GL_DEPTH_COMPONENT32F,
            GL_DEPTH_COMPONENT,
            GL_FLOAT, 4, false
        };
    // DXT-compressed texture formats.
    case Format::RgbDxt1:
        return { GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_RGB, 0, 0, true };
    case Format::RgbaDxt1:
        return { GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_RGBA, 0, 0, true };
    case Format::RgbaDxt3:
        return { GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_RGBA, 0, 0, true };
    case Format::RgbaDxt5:
        return { GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_RGBA, 0, 0, true };
    case Format::SrgbDxt1:
        return { GL_COMPRESSED_SRGB_S3TC_DXT1_EXT, GL_RGB, 0, 0, true };
    case Format::SrgbaDxt1:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT1_EXT, GL_RGBA, 0, 0, true };
    case Format::SrgbaDxt3:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT3_EXT, GL_RGBA, 0, 0, true };
    case Format::SrgbaDxt5:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT5_EXT, GL_RGBA, 0, 0, true };
    default:
        storm_assert_unreachable( "Unexpected format value" );
        return { 0 };
    }
}

unsigned int TextureOgl::getMipLevelsMaximum( const Description &description ) {
    if( description.layout == Layout::Separate2dMsaa ||
        description.layout == Layout::Layered2dMsaa )
    {
        return 1;
    }

    const unsigned int dimensionsMaximum = std::max({
        description.width,
        description.height,
        description.depth
    });

    return static_cast<unsigned int>( log2(dimensionsMaximum) ) + 1;
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Separate1dDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Separate1d;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = 1;
    generalDescription.depth = 1;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = 1;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Separate2dDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Separate2d;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = description.height;
    generalDescription.depth = 1;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = 1;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Separate3dDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Separate3d;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = description.height;
    generalDescription.depth = description.depth;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = 1;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Layered1dDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Layered1d;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = 1;
    generalDescription.depth = 1;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = description.layers;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Layered2dDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Layered2d;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = description.height;
    generalDescription.depth = 1;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = description.layers;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const CubeMapDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::CubeMap;
    generalDescription.format = description.format;
    generalDescription.width = description.dimension;
    generalDescription.height = description.dimension;
    generalDescription.depth = 1;
    generalDescription.mipLevels = description.mipLevels;
    generalDescription.layers = 1;
    generalDescription.texelSamples = 1;
    generalDescription.resourceType = description.resourceType;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Separate2dMsaaDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Separate2dMsaa;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = description.height;
    generalDescription.depth = 1;
    generalDescription.mipLevels = 1;
    generalDescription.layers = 1;
    generalDescription.texelSamples = description.texelSamples;
    generalDescription.resourceType = ResourceType::Dynamic;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

Texture::Pointer Texture::create(
    GpuContext::Pointer gpuContext,
    const Layered2dMsaaDescription &description )
{
    Description generalDescription;
    generalDescription.layout = Layout::Layered2dMsaa;
    generalDescription.format = description.format;
    generalDescription.width = description.width;
    generalDescription.height = description.height;
    generalDescription.depth = 1;
    generalDescription.mipLevels = 1;
    generalDescription.layers = description.layers;
    generalDescription.texelSamples = description.texelSamples;
    generalDescription.resourceType = ResourceType::Dynamic;

    return std::make_shared<TextureOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        generalDescription );
}

}
