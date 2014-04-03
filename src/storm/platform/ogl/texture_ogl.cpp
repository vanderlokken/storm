#include <storm/platform/ogl/texture_ogl.h>

#include <algorithm>
#include <cmath>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

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

    const unsigned int levels​Maximum = getMipLevelsMaximum( _description );
    const unsigned int levels​ = (_description.mipLevels == CompleteMipMap) ?
        levels​Maximum : _description.mipLevels;
    storm_assert( levels​ <= levels​Maximum );

    switch( _description.layout ) {
    case Layout::Separate1d:
        ::glTexStorage1D(
            _target, levels​, _texelDescription.internalFormat,
            description.width );
        checkResult( "::glTexStorage1D" );
        break;
    case Layout::Separate2d:
        ::glTexStorage2D(
            _target, levels​, _texelDescription.internalFormat,
            description.width,
            description.height );
        checkResult( "::glTexStorage2D" );
        break;
    case Layout::Separate3d:
    case Layout::Layered2d:
        ::glTexStorage3D(
            _target, levels​, _texelDescription.internalFormat,
            description.width,
            description.height,
            description.depth );
        checkResult( "::glTexStorage3D" );
        break;
    case Layout::Layered1d:
        ::glTexStorage2D(
            _target, levels​, _texelDescription.internalFormat,
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

    ::glGetTexImage( _target, mipLevel,
        _texelDescription.format, _texelDescription.type, texels );
    checkResult( "::glGetTexImage" );
}

void TextureOgl::setTexels( const Region &region, const void *texels ) {
    storm_assert(
        _description.layout != Layout::Separate2dMsaa &&
        _description.layout != Layout::Layered2dMsaa );

    ScopeTextureBinding scopeTextureBinding( _target, _texture );

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
        return { GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE };
    case Format::ArgbUint8:
        return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE };
    case Format::DepthUint16:
        return { GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE };
    case Format::DepthUint24:
        return { GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE };
    case Format::DepthUint32:
        return { GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE };
    case Format::DepthUint24StencilUint8:
        return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE };
    default:
        storm_assert_unreachable( "Unexpected format value" );
        return { 0 };
    }
}

unsigned int TextureOgl::getMipLevelsMaximum( const Description &description ) {
    unsigned int dimensionsMaximum = 1;

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
