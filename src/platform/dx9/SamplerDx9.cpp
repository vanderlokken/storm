#include "SamplerDx9.h"

#include "Exception.h"

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
    D3DTEXTUREFILTERTYPE result;
    
    if( description.maximalAnisotropyDegree > 1 ) {
        result = D3DTEXF_ANISOTROPIC;
    } else {
        switch( description.minifyingFilter ) {
        case MinifyingFilterNearest:
            result = D3DTEXF_POINT;
            break;
            
        case MinifyingFilterLinear:
        case MinifyingFilterBilinear:
        case MinifyingFilterTrilinear:
            result = D3DTEXF_LINEAR;
            break;
            
        default:
            throwInvalidArgument( "'description.minifyingFilter' is invalid" );
        }
    }
    return result;
}

D3DTEXTUREFILTERTYPE SamplerDx9::selectMagnifyingFilter( const Description &description ) {
    D3DTEXTUREFILTERTYPE result;
    
    if( description.maximalAnisotropyDegree > 1 ) {
        result = D3DTEXF_ANISOTROPIC;
    } else {
        switch( description.magnifyingFilter ) {
        case MagnifyingFilterNearest:
            result = D3DTEXF_POINT;
            break;
            
        case MagnifyingFilterLinear:
            result = D3DTEXF_LINEAR;
            break;
            
        default:
            throwInvalidArgument( "'description.magnifyingFilter' is invalid" );
        }
    }
    return result;
}

D3DTEXTUREFILTERTYPE SamplerDx9::selectMipmappingFilter( const Description &description ) {
    D3DTEXTUREFILTERTYPE result;
    
    switch( description.minifyingFilter ) {
    case MinifyingFilterNearest:
    case MinifyingFilterLinear:
        result = D3DTEXF_NONE;
        break;
        
    case MinifyingFilterBilinear:
        result = D3DTEXF_POINT;
        break;
        
    case MinifyingFilterTrilinear:
        result = D3DTEXF_LINEAR;
        break;
        
    default:
        throwInvalidArgument( "'description.minifyingFilter' is invalid" );
    }
    return result;
}

D3DTEXTUREADDRESS SamplerDx9::convertWrapMode( WrapMode wrapMode ) {
    D3DTEXTUREADDRESS result;
    
    switch( wrapMode ) {
    case WrapClamped:
        result = D3DTADDRESS_CLAMP;
        break;
        
    case WrapRepeated:
        result = D3DTADDRESS_WRAP;
        break;
        
    case WrapMirrored:
        result = D3DTADDRESS_MIRROR;
        break;
        
    case WrapWithBorderColor:
        result = D3DTADDRESS_BORDER;
        break;
        
    default:
        throwInvalidArgument( "'wrapMode' is invalid" );
    }
    return result;
}

}