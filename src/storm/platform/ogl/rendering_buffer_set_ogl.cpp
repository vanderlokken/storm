#include <storm/platform/ogl/rendering_buffer_set_ogl.h>

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

RenderingBufferSetOgl::RenderingBufferSetOgl( const Description &description )
    : _description( description )
{
    ScopeFramebufferBinding scopeFramebufferBinding( _handle );

    auto attachBuffer = []( GLenum attachment​, const Buffer &buffer ) {
        const auto nativeTexture =
            std::static_pointer_cast<TextureOgl>( buffer.texture );

        switch( nativeTexture->getDescription().layout ) {
        case Texture::Layout::Separate1d:
        case Texture::Layout::Separate2d:
        case Texture::Layout::Separate2dMsaa:
            ::glFramebufferTexture( GL_FRAMEBUFFER, attachment​,
                nativeTexture->getHandle(), buffer.mipLevel );
            checkResult( "::glFramebufferTexture" );
            break;
        case Texture::Layout::Layered1d:
        case Texture::Layout::Layered2d:
        case Texture::Layout::Layered2dMsaa:
        case Texture::Layout::Separate3d:
            ::glFramebufferTextureLayer( GL_FRAMEBUFFER, attachment​,
                nativeTexture->getHandle(), buffer.mipLevel, buffer.layer );
            checkResult( "::glFramebufferTextureLayer" );
            break;
        default:
            throwNotImplemented();
        }
    };

    GLenum colorAttachment = GL_COLOR_ATTACHMENT0;

    for( const auto &buffer : description.colorBuffers )
        attachBuffer( colorAttachment++, buffer );

    // TODO: stencil attachment
    attachBuffer( GL_DEPTH_ATTACHMENT, description.depthStencilBuffer );

    storm_assert(
        ::glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE );

    std::vector<GLenum> buffers( description.colorBuffers.size() );
    std::iota( buffers.begin(), buffers.end(), GL_COLOR_ATTACHMENT0 );

    ::glDrawBuffers( buffers.size(), buffers.data() );
    checkResult( "::glDrawBuffers​" );
}

const RenderingBufferSet::Description&
    RenderingBufferSetOgl::getDescription() const
{
    return _description;
}

const FramebufferHandleOgl& RenderingBufferSetOgl::getHandle() const {
    return _handle;
}

RenderingBufferSet::Pointer RenderingBufferSet::create(
    const Description &description )
{
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< RenderingBufferSetOgl >( description );
}

}
