#include <storm/ogl/sampler_ogl.h>

#include <storm/ogl/condition_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

SamplerOgl::SamplerOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description ) :
    _description( description ),
    _handle( gpuContext )
{
    auto setParameter = [&](GLenum parameter, GLint value) {
        gpuContext->call<GlSamplerParameteri>( _handle, parameter, value );
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

    gpuContext->call<GlSamplerParameterfv>(
        _handle, GL_TEXTURE_BORDER_COLOR, &description.borderColor.r );

    if( _description.comparisonCondition ) {
        setParameter( GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE );
        setParameter( GL_TEXTURE_COMPARE_FUNC,
            convertCondition(*_description.comparisonCondition) );
    }

    storm_assert( description.maximalAnisotropyDegree >= 1 );

    if( gpuContext->getExtensionSupportStatus().extTextureFilterAnisotropic ) {
        // http://www.opengl.org/registry/specs/EXT/texture_filter_anisotropic.txt
        #define TEXTURE_MAX_ANISOTROPY_EXT 0x84FE

        gpuContext->call<GlSamplerParameterf>(
            _handle,
            TEXTURE_MAX_ANISOTROPY_EXT,
            static_cast<float>(description.maximalAnisotropyDegree) );
    }
}

const Sampler::Description& SamplerOgl::getDescription() const {
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
        storm_assert_unreachable( "Unexpected minifying filter value" );
        return 0;
    }
}

GLenum SamplerOgl::convertMagnifyingFilter( MagnifyingFilter magnifyingFilter ) {
    switch( magnifyingFilter ) {
    case MagnifyingFilter::Nearest:
        return GL_NEAREST;
    case MagnifyingFilter::Linear:
        return GL_LINEAR;
    default:
        storm_assert_unreachable( "Unexpected magnifying filter value" );
        return 0;
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
        storm_assert_unreachable( "Unexpected wrap mode value" );
        return 0;
    }
}

Sampler::Pointer Sampler::create(
    GpuContext::Pointer gpuContext, const Description &description )
{
    return std::make_shared<SamplerOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        description );
}

}
