#include <storm/platform/ogl/sampler_ogl.h>

#include <storm/exception.h>
#include <storm/platform/ogl/constants_ogl.h>

namespace storm {

SamplerOgl::SamplerOgl( const Description &description )
    : _description( description ),
      _minifyingFilter( convertMinifyingFilter(description.minifyingFilter) ),
      _magnifyingFilter( convertMagnifyingFilter(description.magnifyingFilter) ),
      _borderColor( description.borderColor.get() )
{
    _wrapModes[0] = convertWrapMode( description.wrapModes[0] );
    _wrapModes[1] = convertWrapMode( description.wrapModes[1] );
    _wrapModes[2] = convertWrapMode( description.wrapModes[2] );
    return;
}

const Sampler::Description& SamplerOgl::getDescription() const noexcept {
    return _description;
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

}