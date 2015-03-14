#include <storm/platform/ogl/framebuffer_ogl.h>

#include <numeric>

#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/texture_ogl.h>

namespace storm {

FramebufferHandleOgl::FramebufferHandleOgl() {
    ::glGenFramebuffers( 1, &_handle );
    checkResult( "::glGenFramebuffers" );
}

FramebufferHandleOgl::~FramebufferHandleOgl() {
    ::glDeleteFramebuffers( 1, &_handle );
}

ScopeFramebufferBinding::ScopeFramebufferBinding( GLuint binding ) {
    ::glGetIntegerv( GL_FRAMEBUFFER_BINDING, &_previousBinding );
    checkResult( "::glGetIntegerv" );

    ::glBindFramebuffer( GL_FRAMEBUFFER, binding );
    checkResult( "::glBindFramebuffer" );
}

ScopeFramebufferBinding::~ScopeFramebufferBinding() {
    ::glBindFramebuffer( GL_FRAMEBUFFER, _previousBinding );
}

FramebufferOgl::FramebufferOgl( const Description &description ) :
    _description( description )
{
    ScopeFramebufferBinding scopeFramebufferBinding( _handle );

    size_t colorAttachmentsNumber = 0;

    for( const auto &buffer : description.buffers ) {
        const auto nativeTexture =
            std::static_pointer_cast<TextureOgl>( buffer.texture );

        GLenum attachment;
        switch( nativeTexture->getDescription().format ) {
        case Texture::Format::DepthUint16:
        case Texture::Format::DepthUint24:
        case Texture::Format::DepthUint32:
        case Texture::Format::DepthFloat32:
            attachment = GL_DEPTH_ATTACHMENT;
            break;
        case Texture::Format::DepthUint24StencilUint8:
            attachment = GL_DEPTH_STENCIL_ATTACHMENT;
            break;
        default:
            attachment = GL_COLOR_ATTACHMENT0 + (colorAttachmentsNumber++);
            break;
        }

        switch( nativeTexture->getDescription().layout ) {
        case Texture::Layout::Separate1d:
        case Texture::Layout::Separate2d:
        case Texture::Layout::Separate2dMsaa:
            ::glFramebufferTexture( GL_FRAMEBUFFER, attachment,
                nativeTexture->getHandle(), buffer.mipLevel );
            checkResult( "::glFramebufferTexture" );
            break;
        case Texture::Layout::Layered1d:
        case Texture::Layout::Layered2d:
        case Texture::Layout::Layered2dMsaa:
        case Texture::Layout::Separate3d:
            ::glFramebufferTextureLayer( GL_FRAMEBUFFER, attachment,
                nativeTexture->getHandle(), buffer.mipLevel, buffer.layer );
            checkResult( "::glFramebufferTextureLayer" );
            break;
        default:
            throwNotImplemented();
        }
    }

    storm_assert(
        ::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE );

    std::vector<GLenum> buffers( colorAttachmentsNumber );
    std::iota( buffers.begin(), buffers.end(), GL_COLOR_ATTACHMENT0 );

    ::glDrawBuffers( buffers.size(), buffers.data() );
    checkResult( "::glDrawBuffers​" );
}

const Framebuffer::Description& FramebufferOgl::getDescription() const {
    return _description;
}

const FramebufferHandleOgl& FramebufferOgl::getHandle() const {
    return _handle;
}

Framebuffer::Pointer Framebuffer::create( const Description &description ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< FramebufferOgl >( description );
}

}
