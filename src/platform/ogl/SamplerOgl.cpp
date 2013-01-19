#include "SamplerOgl.h"

#include "ConstantsOgl.h"
#include "Exception.h"

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
    GLenum result;

    switch( minifyingFilter ) {
    case MinifyingFilterNearest:
        result = GL_NEAREST;
        break;

    case MinifyingFilterLinear:
        result = GL_LINEAR;
        break;

    case MinifyingFilterBilinear:
        result = GL_LINEAR_MIPMAP_NEAREST;
        break;

    case MinifyingFilterTrilinear:
        result = GL_LINEAR_MIPMAP_LINEAR;
        break;

    default:
        throwInvalidArgument( "'minifyingFilter' is invalid" );
    }
    return result;
}

GLenum SamplerOgl::convertMagnifyingFilter( MagnifyingFilter magnifyingFilter ) {
    GLenum result;

    switch( magnifyingFilter ) {
    case MagnifyingFilterNearest:
        result = GL_NEAREST;
        break;

    case MagnifyingFilterLinear:
        result = GL_LINEAR;
        break;

    default:
        throwInvalidArgument( "'magnifyingFilter' is invalid" );
    }
    return result;
}

GLenum SamplerOgl::convertWrapMode( WrapMode wrapMode ) {
    GLenum result;

    switch( wrapMode ) {
    case WrapClamped:
        result = GL_CLAMP_TO_EDGE;
        break;

    case WrapRepeated:
        result = GL_REPEAT;
        break;

    case WrapMirrored:
        result = GL_MIRRORED_REPEAT;
        break;

    case WrapWithBorderColor:
        result = GL_CLAMP_TO_BORDER;
        break;

    default:
        throwInvalidArgument( "'wrapMode' is invalid" );
    }
    return result;
}

}