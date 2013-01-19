#include "TextureOgl.h"

#include "CheckResultOgl.h"

namespace storm {

TextureOgl::TextureOgl( const Description &description, const void *texels )
    : _description( description ), _texture( 0 )
{
    ::glGenTextures( 1, &_texture );
    checkResult( "::glGenTextures" );

    try {
        ::glBindTexture( GL_TEXTURE_2D, _texture );
        checkResult( "::glBindTexture" );

        const GLenum target = GL_TEXTURE_2D;
        const GLint level = 0;
        const GLint internalFormat = ...;
        const GLsizei width = _description.dimensions.getWidth();
        const GLsizei height = _description.dimensions.getHeight();
        const GLint border = 0;
        const GLenum format = ...;
        const GLenum type = ...;

        ::glTexImage2D( target, level, internalFormat, width, height, border, format, type, texels );
        checkResult( "::glTexImage2D" );

    } catch( ... ) {
        ::glDeleteTextures( 1, &_texture );
        throw;
    }
    return;
}

TextureOgl::~TextureOgl() noexcept {
    ::glDeleteTextures( 1, &_texture );
    return;
}

void TextureOgl::getTexels( unsigned int lodIndex, void *texels ) const {
    throwRuntimeError( "Not implemented" );
}

void TextureOgl::setTexels( unsigned int lodIndex, const void *texels ) {
    ...
    return;
}

const Texture::Description& TextureOgl::getDescription() const noexcept {
    return _description;
}

}