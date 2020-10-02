#include <storm/ogl/backbuffer_ogl.h>

#include <algorithm>

#include <storm/ogl/texture_ogl.h>

#include <storm/rendering_system.h>
#include <storm/throw_exception.h>
#include <storm/window.h>

namespace storm {

BackbufferOgl::BackbufferOgl( GpuContextOgl::Pointer gpuContext ) :
    _copyFramebuffer( gpuContext )
{
}

void BackbufferOgl::renderTexture(
    Texture::Pointer texture, unsigned int mipLevel, unsigned int layer)
{
    const GpuContextOgl &gpuContext = *_copyFramebuffer.getGpuContext();

    const Texture::Layout textureLayout = texture->getDescription().layout;
    storm_assert(
        textureLayout == Texture::Layout::Separate2d ||
        textureLayout == Texture::Layout::Layered2d  ||
        textureLayout == Texture::Layout::Separate2dMsaa ||
        textureLayout == Texture::Layout::Layered2dMsaa );
    storm_assert(
        texture->getDescription().format == Texture::Format::RgbaNormUint8 ||
        texture->getDescription().format == Texture::Format::SrgbaNormUint8 );

    const ScopeFramebufferBinding scopeFramebufferBinding(
        gpuContext, _copyFramebuffer );

    const auto nativeTexture = std::dynamic_pointer_cast<TextureOgl>( texture );

    storm_assert(
        &gpuContext == nativeTexture->getHandle().getGpuContext().get() );

    if( textureLayout == Texture::Layout::Separate2d ||
        textureLayout == Texture::Layout::Separate2dMsaa )
    {
        gpuContext.call<GlFramebufferTexture>(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            nativeTexture->getHandle(),
            mipLevel );
    } else {
        gpuContext.call<GlFramebufferTextureLayer>(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            nativeTexture->getHandle(),
            mipLevel,
            layer );
    }

    gpuContext.call<GlBindFramebuffer>( GL_DRAW_FRAMEBUFFER, 0 );
    gpuContext.call<GlDrawBuffer>( GL_BACK );
    gpuContext.call<GlReadBuffer>( GL_COLOR_ATTACHMENT0 );

    const Texture::MipLevelDimensions mipLevelDimensions =
        texture->getMipLevelDimensions( mipLevel );

    const GLuint width = mipLevelDimensions.width;
    const GLuint height = mipLevelDimensions.height;

    gpuContext.call<GlBlitFramebuffer>(
        0, 0, width, height,
        0, 0, width, height,
        GL_COLOR_BUFFER_BIT, GL_NEAREST );
}

}
