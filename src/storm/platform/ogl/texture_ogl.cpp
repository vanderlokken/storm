#include <storm/platform/ogl/texture_ogl.h>

#include <algorithm>
#include <cmath>
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
    return;
}

TextureHandleOgl::~TextureHandleOgl() {
    ::glDeleteTextures( 1, &_handle );
    return;
}

class ScopeTextureBinding {
public:
    ScopeTextureBinding( GLenum target, GLuint binding )
        : _target( target )
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

TextureOgl::TextureOgl( const Description &description, const void *texels )
    : _description( description ),
      _texelDescription( selectTexelDescription(description.format) ),
      _target( selectTarget(description.layout) )
{
    validateDescription( description );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    const unsigned int levelsMaximum = getMipLevelsMaximum( _description );
    const unsigned int levels = (_description.mipLevels == CompleteMipMap) ?
        levelsMaximum : _description.mipLevels;
    storm_assert( levels <= levelsMaximum );

    switch( _description.layout ) {
    case Layout::Separate1d:
        ::glTexStorage1D(
            _target, levels, _texelDescription.internalFormat,
            description.width );
        checkResult( "::glTexStorage1D" );
        break;
    case Layout::Separate2d:
        ::glTexStorage2D(
            _target, levels, _texelDescription.internalFormat,
            description.width,
            description.height );
        checkResult( "::glTexStorage2D" );
        break;
    case Layout::Separate3d:
    case Layout::Layered2d:
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
            description.depth );
        checkResult( "::glTexStorage2D" );
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
            description.depth,
            GL_TRUE );
        checkResult( "::glTexStorage3DMultisample" );
        break;
    default:
        throwNotImplemented();
    }

    if( texels )
        throwNotImplemented();
}

void TextureOgl::getTexels( unsigned int mipLevel, void *texels ) const {
    storm_assert(
        _description.layout != Layout::Separate2dMsaa &&
        _description.layout != Layout::Layered2dMsaa );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    if( !_texelDescription.compressed ) {
        ::glGetTexImage( _target, mipLevel,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glGetTexImage" );
    } else {
        ::glGetCompressedTexImage( _target, mipLevel, texels );
        checkResult( "::glGetCompressedTexImage" );
    }
}

void TextureOgl::setTexels( const Region &region, const void *texels ) {
    storm_assert(
        _description.layout != Layout::Separate2dMsaa &&
        _description.layout != Layout::Layered2dMsaa );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

    if( _texelDescription.compressed ) {
        setTexelsCompressed( region, texels );
        return;
    }

    switch( _description.layout ) {
    case Layout::Separate1d:
        ::glTexSubImage1D(
            _target,
            region.mipLevel,
            region.x,
            region.width,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glTexSubImage1D" );
        break;
    case Layout::Separate2d:
        ::glTexSubImage2D(
            _target,
            region.mipLevel,
            region.x,
            region.y,
            region.width,
            region.height,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glTexSubImage2D" );
        break;
    case Layout::Layered2d:
    case Layout::Separate3d:
        ::glTexSubImage3D(
            _target,
            region.mipLevel,
            region.x,
            region.y,
            region.z,
            region.width,
            region.height,
            region.depth,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glTexSubImage3D" );
        break;
    case Layout::Layered1d:
        ::glTexSubImage2D(
            _target,
            region.mipLevel,
            region.x,
            region.z,
            region.width,
            region.depth,
            _texelDescription.format, _texelDescription.type, texels );
        checkResult( "::glTexSubImage2D" );
        break;
    default:
        throwNotImplemented();
    }
}

void TextureOgl::setTexelsCompressed(
    const Region &region, const void *texels )
{
    storm_assert( _description.layout == Layout::Separate2d );

    struct BlockDescription {
        GLsizei width;
        GLsizei height;
        GLsizei size;
    };

    static const std::map<Format, BlockDescription> formatBlockDescriptions = {
        {Format::RgbDxt1, {4, 4, 8}},
        {Format::ArgbDxt1, {4, 4, 8}},
        {Format::ArgbDxt3, {4, 4, 16}},
        {Format::ArgbDxt5, {4, 4, 16}},
        {Format::SrgbDxt1, {4, 4, 8}},
        {Format::AsrgbDxt1, {4, 4, 8}},
        {Format::AsrgbDxt3, {4, 4, 16}},
        {Format::AsrgbDxt5, {4, 4, 16}}
    };

    const BlockDescription &block =
        formatBlockDescriptions.at( _description.format );

    const unsigned int mipLevelWidth =
        std::max( _description.width >> region.mipLevel, 1u );
    const unsigned int mipLevelHeight =
        std::max( _description.height >> region.mipLevel, 1u );

    storm_assert( (region.x % block.width) == 0 );
    storm_assert( (region.y % block.height) == 0 );
    storm_assert( (region.width % block.width) == 0 ||
        region.x + region.width == mipLevelWidth );
    storm_assert( (region.height % block.height) == 0 ||
        region.y + region.height == mipLevelHeight );

    const GLsizei dataSize =
        static_cast<GLsizei>( ceil(1.0f * region.width / block.width) ) *
        static_cast<GLsizei>( ceil(1.0f * region.height / block.height) ) *
        block.size;

    ::glCompressedTexSubImage2D(
        _target,
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

void TextureOgl::generateMipMap() {
    storm_assert(
        _description.layout != Layout::Separate2dMsaa &&
        _description.layout != Layout::Layered2dMsaa &&
        _description.layout != Layout::Buffer );

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

void TextureOgl::validateDescription( const Description &description ) {
    switch( description.layout ) {
    case Layout::Separate1d:
        storm_assert( description.height == 1 );
        storm_assert( description.depth == 1 );
        storm_assert( description.texelSamples == 1 );
        return;
    case Layout::Separate2d:
        storm_assert( description.depth == 1 );
        storm_assert( description.texelSamples == 1 );
        return;
    case Layout::Separate2dMsaa:
        storm_assert( description.depth == 1 );
        storm_assert( description.mipLevels == 1 );
        storm_assert( description.resourceType == ResourceType::Dynamic );
        return;
    case Layout::Separate3d:
        storm_assert( description.texelSamples == 1 );
        return;
    case Layout::Layered1d:
        storm_assert( description.height == 1 );
        storm_assert( description.texelSamples == 1 );
        return;
    case Layout::Layered2d:
        storm_assert( description.texelSamples == 1 );
        return;
    case Layout::Layered2dMsaa:
        storm_assert( description.mipLevels == 1 );
        storm_assert( description.resourceType == ResourceType::Dynamic );
        return;
    case Layout::CubeMap:
        throwNotImplemented();
    case Layout::Buffer:
        storm_assert( description.height == 1 );
        storm_assert( description.depth == 1 );
        storm_assert( description.texelSamples == 1 );
        storm_assert( description.mipLevels == 1 );
        return;
    default:
        storm_assert_unreachable( "Unexpected layout value" );
    }

    if( description.format == Format::RgbDxt1 ||
        description.format == Format::ArgbDxt1 ||
        description.format == Format::ArgbDxt3 ||
        description.format == Format::ArgbDxt5 ||
        description.format == Format::SrgbDxt1 ||
        description.format == Format::AsrgbDxt1 ||
        description.format == Format::AsrgbDxt3 ||
        description.format == Format::AsrgbDxt5 )
    {
        storm_assert( description.layout == Layout::Separate2d );
    }
}

GLenum TextureOgl::selectTarget( Layout layout ) {
    switch( layout ) {
    case Layout::Separate1d:
        return GL_TEXTURE_1D;
    case Layout::Separate2d:
        return GL_TEXTURE_2D;
    case Layout::Separate2dMsaa:
        return GL_TEXTURE_2D_MULTISAMPLE;
    case Layout::Separate3d:
        return GL_TEXTURE_3D;
    case Layout::Layered1d:
        return GL_TEXTURE_1D_ARRAY;
    case Layout::Layered2d:
        return GL_TEXTURE_2D_ARRAY;
    case Layout::Layered2dMsaa:
        return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    case Layout::CubeMap:
        return GL_TEXTURE_CUBE_MAP;
    case Layout::Buffer:
        return GL_TEXTURE_BUFFER;
    default:
        storm_assert_unreachable( "Unexpected layout value" );
        return 0;
    }
}

TextureOgl::TexelDescription TextureOgl::selectTexelDescription( Format format )
{
    switch( format ) {
    case Format::RgbUint8:
        return { GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE, false };
    case Format::ArgbUint8:
        return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, false };
    case Format::SrgbUint8:
        return { GL_SRGB8_ALPHA8, GL_RGB, GL_UNSIGNED_BYTE, false };
    case Format::AsrgbUint8:
        return { GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE, false };
    case Format::RedFloat16:
        return { GL_R16F, GL_RED, GL_HALF_FLOAT, false };
    case Format::RgFloat16:
        return { GL_RG16F, GL_RG, GL_HALF_FLOAT, false };
    case Format::RgbFloat16:
        return { GL_RGB16F, GL_RGB, GL_HALF_FLOAT, false };
    case Format::RgbaFloat16:
        return { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, false };
    case Format::RedFloat32:
        return { GL_R32F, GL_RED, GL_FLOAT, false };
    case Format::RgFloat32:
        return { GL_RG32F, GL_RG, GL_FLOAT, false };
    case Format::RgbFloat32:
        return { GL_RGB32F, GL_RGB, GL_FLOAT, false };
    case Format::RgbaFloat32:
        return { GL_RGBA32F, GL_RGBA, GL_FLOAT, false };
    case Format::DepthUint16:
        return { GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, false };
    case Format::DepthUint24:
        return { GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, false };
    case Format::DepthUint32:
        return { GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, false };
    case Format::DepthUint24StencilUint8:
        return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, false };
    case Format::DepthFloat32:
        return { GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, false };
    case Format::RgbDxt1:
        return { GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_RGB, 0, true };
    case Format::ArgbDxt1:
        return { GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_RGBA, 0, true };
    case Format::ArgbDxt3:
        return { GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_RGBA, 0, true };
    case Format::ArgbDxt5:
        return { GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_RGBA, 0, true };
    case Format::SrgbDxt1:
        return { GL_COMPRESSED_SRGB_S3TC_DXT1_EXT, GL_RGB, 0, true };
    case Format::AsrgbDxt1:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT1_EXT, GL_RGBA, 0, true };
    case Format::AsrgbDxt3:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT3_EXT, GL_RGBA, 0, true };
    case Format::AsrgbDxt5:
        return { GL_COMPRESSED_SRGBA_S3TC_DXT5_EXT, GL_RGBA, 0, true };
    default:
        storm_assert_unreachable( "Unexpected format value" );
        return { 0 };
    }
}

unsigned int TextureOgl::getMipLevelsMaximum( const Description &description ) {
    unsigned int dimensionsMaximum;

    switch( description.layout ) {
    case Layout::Separate1d:
    case Layout::Layered1d:
        dimensionsMaximum = description.width;
        break;
    case Layout::Separate2d:
    case Layout::Layered2d:
        dimensionsMaximum = std::max( description.width, description.height );
        break;
    case Layout::Separate3d:
        dimensionsMaximum = std::max(
            {description.width, description.height, description.depth} );
        break;
    case Layout::CubeMap:
        throwNotImplemented();
        break;
    default:
        dimensionsMaximum = 1;
        break;
    }

    return static_cast<unsigned int>( log2(dimensionsMaximum) ) + 1;
}

Texture::Pointer Texture::create(
    const Description &description, const void *texels )
{
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< TextureOgl >( description, texels );
}

}
