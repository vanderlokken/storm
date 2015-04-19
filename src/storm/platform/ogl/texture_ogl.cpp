#include <storm/platform/ogl/texture_ogl.h>

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <map>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

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

TextureHandleOgl::TextureHandleOgl() {
    ::glGenTextures( 1, &_handle );
    checkResult( "::glGenTextures" );
}

TextureHandleOgl::~TextureHandleOgl() {
    ::glDeleteTextures( 1, &_handle );
}

class ScopeTextureBinding {
public:
    ScopeTextureBinding( GLenum target, GLuint binding ) :
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

        ::glGetIntegerv( bindingEnumeration, &_previousBinding );
        checkResult( "::glGetIntegerv" );

        ::glBindTexture( target, binding );
        checkResult( "::glBindTexture" );
    }

    ~ScopeTextureBinding() {
        ::glBindTexture( _target, _previousBinding );
    }

private:
    GLenum _target;
    GLint _previousBinding;
};

TextureOgl::TextureOgl( const Description &description ) :
    _description( description ),
    _texelDescription( selectTexelDescription(description.format) ),
    _target( selectTarget(description.layout) )
{
    validateDescription();

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    const unsigned int levelsMaximum = getMipLevelsMaximum( _description );
    const unsigned int levels = _description.mipLevels == CompleteMipMap ?
        levelsMaximum : _description.mipLevels;
    storm_assert( levels <= levelsMaximum );

    if( _description.mipLevels == CompleteMipMap )
        _description.mipLevels = levels;

    switch( _description.layout ) {
    case Layout::Separate1d:
        ::glTexStorage1D(
            _target, levels, _texelDescription.internalFormat,
            description.width );
        checkResult( "::glTexStorage1D" );
        break;
    case Layout::Separate2d:
    case Layout::CubeMap:
        ::glTexStorage2D(
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height );
        checkResult( "::glTexStorage2D" );
        break;
    case Layout::Separate3d:
        ::glTexStorage3D(
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height,
            description.depth );
        checkResult( "::glTexStorage3D" );
        break;
    case Layout::Layered1d:
        ::glTexStorage2D(
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.layers );
        checkResult( "::glTexStorage2D" );
        break;
    case Layout::Layered2d:
        ::glTexStorage3D(
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height,
            description.layers );
        checkResult( "::glTexStorage3D" );
        break;
    case Layout::Separate2dMsaa:
        ::glTexStorage2DMultisample(
            _target, description.texelSamples,
            _texelDescription.internalFormat,
            description.width,
            description.height,
            GL_TRUE );
        checkResult( "::glTexStorage2DMultisample" );
        break;
    case Layout::Layered2dMsaa:
        ::glTexStorage3DMultisample(
            _target, description.texelSamples,
            _texelDescription.internalFormat,
            description.width,
            description.height,
            description.layers,
            GL_TRUE );
        checkResult( "::glTexStorage3DMultisample" );
        break;
    default:
        throwNotImplemented();
    }
}

void TextureOgl::getTexels(
    unsigned int mipLevel, unsigned int size, void *texels ) const
{
    storm_assert( _description.layout != Layout::Separate2dMsaa );
    storm_assert( _description.layout != Layout::Layered2dMsaa );

    storm_assert( mipLevel < _description.mipLevels );

    // TODO: check size

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    if( _description.layout == Layout::CubeMap )
        throwNotImplemented();

    if( !_texelDescription.compressed ) {
        setTexelTransferAlignment( getMipLevelDimensions(mipLevel).width );

        ::glGetTexImage( _target, mipLevel,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glGetTexImage" );

        resetTexelTransferAlignment();
    } else {
        ::glGetCompressedTexImage( _target, mipLevel, texels );
        checkResult( "::glGetCompressedTexImage" );
    }
}

void TextureOgl::setTexels(
    const Separate1dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate1d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    ::glTexSubImage1D(
        _target,
        region.mipLevel,
        region.x,
        region.width,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage1D" );
}

void TextureOgl::setTexels(
    const Separate2dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate2d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    if( _texelDescription.compressed ) {
        CompressedRegion compressedRegion;

        compressedRegion.target = _target;
        compressedRegion.mipLevel = region.mipLevel;
        compressedRegion.x = region.x;
        compressedRegion.y = region.y;
        compressedRegion.width = region.width;
        compressedRegion.height = region.height;

        setTexelsCompressed( compressedRegion, data );
        return;
    }

    setTexelTransferAlignment( region.width );

    ::glTexSubImage2D(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.width,
        region.height,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage2D" );

    resetTexelTransferAlignment();
}

void TextureOgl::setTexels(
    const Separate3dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Separate3d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );
    storm_assert( region.z + region.depth <= mipLevelDimensions.depth );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    setTexelTransferAlignment( region.width );

    ::glTexSubImage3D(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.z,
        region.width,
        region.height,
        region.depth,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage3D" );

    resetTexelTransferAlignment();
}

void TextureOgl::setTexels(
    const Layered1dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Layered1d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.layer < _description.layers );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    ::glTexSubImage2D(
        _target,
        region.mipLevel,
        region.x,
        region.layer,
        region.width,
        /* depth = */ 1,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage2D" );
}

void TextureOgl::setTexels(
    const Layered2dRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::Layered2d );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.layer < _description.layers );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    setTexelTransferAlignment( region.width );

    ::glTexSubImage3D(
        _target,
        region.mipLevel,
        region.x,
        region.y,
        region.layer,
        region.width,
        region.height,
        /* depth = */ 1,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage3D" );

    resetTexelTransferAlignment();
}

void TextureOgl::setTexels(
    const CubeMapRegion &region, const void *data )
{
    storm_assert( _description.layout == Layout::CubeMap );

    const MipLevelDimensions mipLevelDimensions =
        getMipLevelDimensions( region.mipLevel );

    storm_assert( region.mipLevel < _description.mipLevels );
    storm_assert( region.face >= CubeMapFace::PositiveX );
    storm_assert( region.face <= CubeMapFace::NegativeZ );
    storm_assert( region.x + region.width <= mipLevelDimensions.width );
    storm_assert( region.y + region.height <= mipLevelDimensions.height );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    static const GLenum faces[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    if( _texelDescription.compressed ) {
        CompressedRegion compressedRegion;

        compressedRegion.target = faces[region.face];
        compressedRegion.mipLevel = region.mipLevel;
        compressedRegion.x = region.x;
        compressedRegion.y = region.y;
        compressedRegion.width = region.width;
        compressedRegion.height = region.height;

        setTexelsCompressed( compressedRegion, data );
        return;
    }

    setTexelTransferAlignment( region.width );

    ::glTexSubImage2D(
        faces[region.face],
        region.mipLevel,
        region.x,
        region.y,
        region.width,
        region.height,
        _texelDescription.format, _texelDescription.type, data );
    checkResult( "::glTexSubImage2D" );

    resetTexelTransferAlignment();
}

void TextureOgl::generateMipMap() {
    storm_assert( _description.layout != Layout::Separate2dMsaa );
    storm_assert( _description.layout != Layout::Layered2dMsaa );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    ::glGenerateMipmap( _target );
    checkResult( "::glGenerateMipmap" );
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
            _description.layout == Layout::CubeMap );
    }
}

void TextureOgl::setTexelTransferAlignment( unsigned int width ) const {
    const std::initializer_list<unsigned int> alignments = {4, 2, 1};

    auto isSuitable = [=]( unsigned int alignment ) {
        return (_texelDescription.size * width) % alignment == 0;
    };

    const unsigned int *alignment = std::find_if(
        alignments.begin(),
        alignments.end(),
        isSuitable );

    ::glPixelStorei( GL_PACK_ALIGNMENT, *alignment );
    checkResult( "::glPixelStorei" );

    ::glPixelStorei( GL_UNPACK_ALIGNMENT, *alignment );
    checkResult( "::glPixelStorei" );
}

void TextureOgl::resetTexelTransferAlignment() const {
    ::glPixelStorei( GL_PACK_ALIGNMENT, 4 );
    checkResult( "::glPixelStorei" );

    ::glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
    checkResult( "::glPixelStorei" );
}

void TextureOgl::setTexelsCompressed(
    const CompressedRegion &region, const void *texels )
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

    storm_assert( (region.x % block.width) == 0 );
    storm_assert( (region.y % block.height) == 0 );
    storm_assert( (region.width % block.width) == 0 ||
        region.x + region.width == mipLevelDimensions.width );
    storm_assert( (region.height % block.height) == 0 ||
        region.y + region.height == mipLevelDimensions.height );

    const GLsizei dataSize =
        static_cast<GLsizei>( ceil(1.0f * region.width / block.width) ) *
        static_cast<GLsizei>( ceil(1.0f * region.height / block.height) ) *
        block.size;

    ::glCompressedTexSubImage2D(
        region.target,
        region.mipLevel,
        region.x,
        region.y,
        region.width,
        region.height,
        _texelDescription.internalFormat,
        dataSize,
        texels );
    checkResult( "::glCompressedTexSubImage2D" );
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
    case Format::RgbUint8:
        return { GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE, 3, false };
    case Format::RgbaUint8:
        return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, false };
    case Format::SrgbUint8:
        return { GL_SRGB8_ALPHA8, GL_RGB, GL_UNSIGNED_BYTE, 3, false };
    case Format::SrgbaUint8:
        return { GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE, 4, false };
    case Format::RedFloat16:
        return { GL_R16F, GL_RED, GL_HALF_FLOAT, 2, false };
    case Format::RgFloat16:
        return { GL_RG16F, GL_RG, GL_HALF_FLOAT, 4, false };
    case Format::RgbFloat16:
        return { GL_RGB16F, GL_RGB, GL_HALF_FLOAT, 6, false };
    case Format::RgbaFloat16:
        return { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, 8, false };
    case Format::RedFloat32:
        return { GL_R32F, GL_RED, GL_FLOAT, 4, false };
    case Format::RgFloat32:
        return { GL_RG32F, GL_RG, GL_FLOAT, 8, false };
    case Format::RgbFloat32:
        return { GL_RGB32F, GL_RGB, GL_FLOAT, 12, false };
    case Format::RgbaFloat32:
        return { GL_RGBA32F, GL_RGBA, GL_FLOAT, 16, false };
    case Format::DepthUint16:
        return {
            GL_DEPTH_COMPONENT16,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_SHORT, 2, false
        };
    case Format::DepthUint24:
        return {
            GL_DEPTH_COMPONENT24,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_INT, 4, false
        };
    case Format::DepthUint32:
        return {
            GL_DEPTH_COMPONENT32,
            GL_DEPTH_COMPONENT,
            GL_UNSIGNED_INT, 4, false
        };
    case Format::DepthUint24StencilUint8:
        return {
            GL_DEPTH24_STENCIL8,
            GL_DEPTH_STENCIL,
            GL_UNSIGNED_INT_24_8, 8, false
        };
    case Format::DepthFloat32:
        return {
            GL_DEPTH_COMPONENT32F,
            GL_DEPTH_COMPONENT,
            GL_FLOAT, 4, false
        };
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

Texture::Pointer Texture::create( const Separate1dDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create( const Separate2dDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create( const Separate3dDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create( const Layered1dDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create( const Layered2dDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create( const CubeMapDescription &description ) {
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create(
    const Separate2dMsaaDescription &description )
{
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

Texture::Pointer Texture::create(
    const Layered2dMsaaDescription &description )
{
    RenderingSystemOgl::installOpenGlContext();

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

    return std::make_shared< TextureOgl >( generalDescription );
}

}
