#include <storm/ogl/framebuffer_ogl.h>

#include <numeric>

#include <storm/ogl/texture_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

ScopeFramebufferBinding::ScopeFramebufferBinding(
        const GpuContextOgl &gpuContext, GLuint binding ) :
    _gpuContext( gpuContext )
{
    _gpuContext.call<GlGetIntegerv>(
        GL_FRAMEBUFFER_BINDING, &_previousBinding );
    _gpuContext.call<GlBindFramebuffer>(
        GL_FRAMEBUFFER, binding );
}

ScopeFramebufferBinding::~ScopeFramebufferBinding() {
    _gpuContext.callUnchecked<GlBindFramebuffer>(
        GL_FRAMEBUFFER, _previousBinding );
}

FramebufferOgl::FramebufferOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description ) :
    _description( description ),
    _handle( gpuContext )
{
    ScopeFramebufferBinding scopeFramebufferBinding( *gpuContext, _handle );

    size_t colorAttachmentsNumber = 0;
    size_t depthAttachmentsNumber = 0;

    for( const auto &buffer : description.buffers ) {
        const auto nativeTexture =
            std::dynamic_pointer_cast<TextureOgl>( buffer.texture );

        storm_assert(
            gpuContext == nativeTexture->getHandle().getGpuContext() );

        GLenum attachment;
        switch( nativeTexture->getDescription().format ) {
        case Texture::Format::DepthNormUint16:
        case Texture::Format::DepthNormUint24:
        case Texture::Format::DepthNormUint32:
        case Texture::Format::DepthFloat32:
            storm_assert( depthAttachmentsNumber == 0 );
            ++depthAttachmentsNumber;
            attachment = GL_DEPTH_ATTACHMENT;
            break;

        case Texture::Format::DepthNormUint24StencilUint8:
            storm_assert( depthAttachmentsNumber == 0 );
            ++depthAttachmentsNumber;
            attachment = GL_DEPTH_STENCIL_ATTACHMENT;
            break;

        default:
            attachment = GL_COLOR_ATTACHMENT0 +
                static_cast<GLenum>( colorAttachmentsNumber++ );
            break;
        }

        switch( nativeTexture->getDescription().layout ) {
        case Texture::Layout::Separate1d:
        case Texture::Layout::Separate2d:
        case Texture::Layout::Separate2dMsaa:
            gpuContext->call<GlFramebufferTexture>(
                GL_FRAMEBUFFER,
                attachment,
                nativeTexture->getHandle(),
                buffer.mipLevel );
            break;
        case Texture::Layout::Layered1d:
        case Texture::Layout::Layered2d:
        case Texture::Layout::Layered2dMsaa:
        case Texture::Layout::Separate3d:
            gpuContext->call<GlFramebufferTextureLayer>(
                GL_FRAMEBUFFER,
                attachment,
                nativeTexture->getHandle(),
                buffer.mipLevel,
                buffer.layer );
            break;
        case Texture::Layout::CubeMap:
            gpuContext->call<GlFramebufferTexture2D>(
                GL_FRAMEBUFFER,
                attachment,
                TextureOgl::convertCubeMapFace(buffer.layer),
                nativeTexture->getHandle(),
                buffer.mipLevel );
            break;
        default:
            throwNotImplemented();
        }
    }

    storm_assert(
        gpuContext->callUnchecked<GlCheckFramebufferStatus>(GL_FRAMEBUFFER) ==
            GL_FRAMEBUFFER_COMPLETE );

    std::vector<GLenum> buffers( colorAttachmentsNumber );
    std::iota( buffers.begin(), buffers.end(), GL_COLOR_ATTACHMENT0 );

    gpuContext->call<GlDrawBuffers>(
        static_cast<GLsizei>(buffers.size()), buffers.data() );
}

const Framebuffer::Description& FramebufferOgl::getDescription() const {
    return _description;
}

const FramebufferHandleOgl& FramebufferOgl::getHandle() const {
    return _handle;
}

Framebuffer::Pointer Framebuffer::create(
    GpuContext::Pointer gpuContext, const Description &description )
{
    return std::make_shared<FramebufferOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        description );
}

}
