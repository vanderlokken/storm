#include <storm/platform/ogl/sampler_ogl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>

namespace storm {

SamplerHandleOgl::SamplerHandleOgl() {
    ::glGenSamplers( 1, &_handle );
    checkResult( "::glGenSamplers" );
    return;
}

SamplerHandleOgl::~SamplerHandleOgl() {
    ::glDeleteSamplers( 1, &_handle );
    return;
}

SamplerOgl::SamplerOgl( const Description &description )
    : _description( description )
{
    auto setParameter = [this](GLenum parameter, GLint value) {
        ::glSamplerParameteri( _handle, parameter, value );
        checkResult( "::glSamplerParameteri" );
    };

    setParameter( GL_TEXTURE_MIN_FILTER,
        convertMinifyingFilter(description.minifyingFilter) );
    setParameter( GL_TEXTURE_MAG_FILTER,
        convertMagnifyingFilter(description.magnifyingFilter) );
    setParameter( GL_TEXTURE_WRAP_S,
        convertWrapMode(description.wrapModes[0]) );
    setParameter( GL_TEXTURE_WRAP_T,
        convertWrapMode(description.wrapModes[1]) );
    setParameter( GL_TEXTURE_WRAP_R,
        convertWrapMode(description.wrapModes[2]) );

    const float color[] = {
        description.borderColor.getNormalizedR(),
        description.borderColor.getNormalizedG(),
        description.borderColor.getNormalizedB(),
        description.borderColor.getNormalizedA()
    };
    ::glSamplerParameterfv( _handle, GL_TEXTURE_BORDER_COLOR, color );
    checkResult( "::glSamplerParameterfv" );

    // http://www.opengl.org/registry/specs/EXT/texture_filter_anisotropic.txt
    #define TEXTURE_MAX_ANISOTROPY_EXT 0x84FE

    ::glSamplerParameterf( _handle, TEXTURE_MAX_ANISOTROPY_EXT,
        static_cast< float >(description.maximalAnisotropyDegree) );
    checkResult( "::glSamplerParameterf" );
}

const Sampler::Description& SamplerOgl::getDescription() const noexcept {
    return _description;
}

const SamplerHandleOgl& SamplerOgl::getHandle() const {
    return _handle;
}

GLenum SamplerOgl::convertMinifyingFilter( MinifyingFilter minifyingFilter ) {
    switch( minifyingFilter ) {
    case MinifyingFilter::Nearest:
        return GL_NEAREST;
    case MinifyingFilter::Linear:
        return GL_LINEAR;
    case MinifyingFilter::Bilinear:
        return GL_LINEAR_MIPMAP_NEAREST;
    case MinifyingFilter::Trilinear:
        return GL_LINEAR_MIPMAP_LINEAR;
    default:
        throwInvalidArgument( "'minifyingFilter' is invalid" );
    }
}

GLenum SamplerOgl::convertMagnifyingFilter( MagnifyingFilter magnifyingFilter ) {
    switch( magnifyingFilter ) {
    case MagnifyingFilter::Nearest:
        return GL_NEAREST;
    case MagnifyingFilter::Linear:
        return GL_LINEAR;
    default:
        throwInvalidArgument( "'magnifyingFilter' is invalid" );
    }
}

GLenum SamplerOgl::convertWrapMode( WrapMode wrapMode ) {
    switch( wrapMode ) {
    case WrapMode::Clamped:
        return GL_CLAMP_TO_EDGE;
    case WrapMode::Repeated:
        return GL_REPEAT;
    case WrapMode::Mirrored:
        return GL_MIRRORED_REPEAT;
    case WrapMode::WithBorderColor:
        return GL_CLAMP_TO_BORDER;
    default:
        throwInvalidArgument( "'wrapMode' is invalid" );
    }
}

Sampler::Pointer Sampler::create( const Description &description ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< SamplerOgl >( description );
}

}
