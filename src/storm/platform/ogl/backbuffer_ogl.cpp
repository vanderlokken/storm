#include <storm/platform/ogl/backbuffer_ogl.h>

#include <algorithm>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/texture_ogl.h>

#include <storm/rendering_system.h>
#include <storm/rendering_window.h>

namespace storm {

void BackbufferOgl::renderTexture(
    Texture::Pointer texture, unsigned int mipLevel, unsigned int layer)
{
    const Texture::Layout textureLayout = texture->getDescription().layout;
    storm_assert(
        textureLayout == Texture::Layout::Separate2d ||
        textureLayout == Texture::Layout::Layered2d  ||
        textureLayout == Texture::Layout::Separate2dMsaa ||
        textureLayout == Texture::Layout::Layered2dMsaa );
    storm_assert(
        texture->getDescription().format == Texture::Format::ArgbUint8 ||
        texture->getDescription().format == Texture::Format::AsrgbUint8 );

    ScopeFramebufferBinding scopedFramebufferBinding( _copyFramebuffer );

    const auto nativeTexture = std::static_pointer_cast<TextureOgl>( texture );

    if( textureLayout == Texture::Layout::Separate2d ||
        textureLayout == Texture::Layout::Separate2dMsaa )
    {
        ::glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            nativeTexture->getHandle(), mipLevel );
        checkResult( "::glFramebufferTexture" );
    } else {
        ::glFramebufferTextureLayer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            nativeTexture->getHandle(), mipLevel, layer );
        checkResult( "::glFramebufferTextureLayer" );
    }

    ::glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
    checkResult( "::glBindFramebuffer" );

    ::glDrawBuffer( GL_BACK );
    checkResult( "::glDrawBuffer" );

    ::glReadBuffer( GL_COLOR_ATTACHMENT0 );
    checkResult( "::glReadBuffer" );

    const Dimensions dimensions =
        RenderingWindow::getInstance()->getDimensions();
    const GLuint width = dimensions.width;
    const GLuint height = dimensions.height;

    storm_assert(
        std::max(texture->getDescription().width >> mipLevel, 1u) == width );
    storm_assert(
        std::max(texture->getDescription().height >> mipLevel, 1u) == height );

    ::glBlitFramebuffer( 0, 0, width, height, 0, 0, width, height,
        GL_COLOR_BUFFER_BIT, GL_NEAREST );
    checkResult( "::glBlitFramebuffer" );
}

}
