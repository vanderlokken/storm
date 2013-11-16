#include <storm/platform/dx9/sampler_dx9.h>

#include <storm/exception.h>

namespace storm {

SamplerDx9::SamplerDx9( const Description &description )
    : _description( description ),
      _minifyingFilter( selectMinifyingFilter(description) ),
      _magnifyingFilter( selectMagnifyingFilter(description) ),
      _mipmappingFilter( selectMipmappingFilter(description) ),
      _borderColor( description.borderColor.get() )
{
    _wrapModes[0] = convertWrapMode( _description.wrapModes[0] );
    _wrapModes[1] = convertWrapMode( _description.wrapModes[1] );
    _wrapModes[2] = convertWrapMode( _description.wrapModes[2] );
    return;
}

const Sampler::Description& SamplerDx9::getDescription() const noexcept {
    return _description;
}

D3DTEXTUREFILTERTYPE SamplerDx9::selectMinifyingFilter( const Description &description ) {
    if( description.maximalAnisotropyDegree > 1 ) {
        return D3DTEXF_ANISOTROPIC;
    } else {
        switch( description.minifyingFilter ) {
        case MinifyingFilter::Nearest:
            return D3DTEXF_POINT;
        case MinifyingFilter::Linear:
        case MinifyingFilter::Bilinear:
        case MinifyingFilter::Trilinear:
            return D3DTEXF_LINEAR;
        default:
            throwInvalidArgument( "'description.minifyingFilter' is invalid" );
        }
    }
}

D3DTEXTUREFILTERTYPE SamplerDx9::selectMagnifyingFilter( const Description &description ) {
    if( description.maximalAnisotropyDegree > 1 ) {
        return D3DTEXF_ANISOTROPIC;
    } else {
        switch( description.magnifyingFilter ) {
        case MagnifyingFilter::Nearest:
            return D3DTEXF_POINT;
        case MagnifyingFilter::Linear:
            return D3DTEXF_LINEAR;
        default:
            throwInvalidArgument( "'description.magnifyingFilter' is invalid" );
        }
    }
}

D3DTEXTUREFILTERTYPE SamplerDx9::selectMipmappingFilter( const Description &description ) {
    switch( description.minifyingFilter ) {
    case MinifyingFilter::Nearest:
    case MinifyingFilter::Linear:
        return D3DTEXF_NONE;
    case MinifyingFilter::Bilinear:
        return D3DTEXF_POINT;
    case MinifyingFilter::Trilinear:
        return D3DTEXF_LINEAR;
    default:
        throwInvalidArgument( "'description.minifyingFilter' is invalid" );
    }
}

D3DTEXTUREADDRESS SamplerDx9::convertWrapMode( WrapMode wrapMode ) {
    switch( wrapMode ) {
    case WrapMode::Clamped:
        return D3DTADDRESS_CLAMP;
    case WrapMode::Repeated:
        return D3DTADDRESS_WRAP;
    case WrapMode::Mirrored:
        return D3DTADDRESS_MIRROR;
    case WrapMode::WithBorderColor:
        return D3DTADDRESS_BORDER;
    default:
        throwInvalidArgument( "'wrapMode' is invalid" );
    }
}

}
