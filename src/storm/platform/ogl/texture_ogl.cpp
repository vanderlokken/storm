#include <storm/platform/ogl/texture_ogl.h>

#include <algorithm>

#include <storm/platform/ogl/check_result_ogl.h>

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

TextureOgl::TextureOgl( const Description &description, const void *texels )
    : _description( description )
{
    // TODO: use glTexStorage2D if possible

    if( texels )
        setTexels( 0, texels );

    return;
}

void TextureOgl::getTexels( unsigned int lodIndex, void *texels ) const {
    throwRuntimeError( "Not implemented" );
}

void TextureOgl::setTexels( unsigned int lodIndex, const void *texels ) {

    ::glBindTexture( GL_TEXTURE_2D, _texture );
    checkResult( "::glBindTexture" );

    const GLenum target = GL_TEXTURE_2D;
    const GLint level = lodIndex;
    const GLint internalFormat = selectInternalFormat( _description.format );
    const GLsizei width =
        std::max( _description.dimensions.getWidth() >> lodIndex, 1U );
    const GLsizei height =
        std::max( _description.dimensions.getHeight() >> lodIndex, 1U );
    const GLint border = 0;
    const GLenum format = convertFormat( _description.format );
    const GLenum type = GL_UNSIGNED_BYTE;

    ::glTexImage2D( target, level, internalFormat, width, height, border,
        format, type, texels );
    checkResult( "::glTexImage2D" );

    if( _description.lodGenerationMode == LodGenerationMode::Automatic &&
        lodIndex == 0 )
    {
        ::glGenerateMipmap( GL_TEXTURE_2D );
        checkResult( "::glGenerateMipmap" );
    }

    return;
}

const TextureHandleOgl& TextureOgl::getHandle() const noexcept {
    return _texture;
}

GLenum TextureOgl::convertFormat( Format format ) {
    switch( format ) {
    case Format::XrgbUint8:
        return GL_RGB;
    case Format::ArgbUint8:
        return GL_RGBA;
    default:
        throwInvalidArgument( "'format' is invalid" );
    }
}

GLint TextureOgl::selectInternalFormat( Format format ) {
    switch( format ) {
    case Format::XrgbUint8:
    case Format::ArgbUint8:
        return GL_BGRA;
    default:
        throwInvalidArgument( "'format' is invalid" );
    }
}

const Texture::Description& TextureOgl::getDescription() const noexcept {
    return _description;
}

}
