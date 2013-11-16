#include <storm/platform/dx9/blending_technique_dx9.h>

#include <storm/exception.h>

namespace storm {

BlendingTechniqueDx9::BlendingTechniqueDx9( const Description &description )
    : _description( description ),
      _operation( convertOperation(description.operation) ),
      _sourceFactor( convertFactor(description.sourceFactor) ),
      _destinationFactor( convertFactor(description.destinationFactor) )
{
    return;
}

const BlendingTechnique::Description& BlendingTechniqueDx9::getDescription() const noexcept {
    return _description;
}

D3DBLENDOP BlendingTechniqueDx9::getOperation() const noexcept {
    return _operation;
}

D3DBLEND BlendingTechniqueDx9::getSourceFactor() const noexcept {
    return _sourceFactor;
}

D3DBLEND BlendingTechniqueDx9::getDestinationFactor() const noexcept {
    return _destinationFactor;
}

D3DBLENDOP BlendingTechniqueDx9::convertOperation( Operation operation ) {
    switch( operation ) {
    case Operation::Addition:
        return D3DBLENDOP_ADD;
    case Operation::Subtraction:
        return D3DBLENDOP_SUBTRACT;
    case Operation::NegativeSubtraction:
        return D3DBLENDOP_REVSUBTRACT;
    case Operation::Minimum:
        return D3DBLENDOP_MIN;
    case Operation::Maximum:
        return D3DBLENDOP_MAX;
    default:
        throwInvalidArgument( "'operation' is invalid" );
    }
}

D3DBLEND BlendingTechniqueDx9::convertFactor( Factor factor ) {
    switch( factor ) {
    case Factor::Zero:
        return D3DBLEND_ZERO;
    case Factor::One:
        return D3DBLEND_ONE;
    case Factor::SourceColor:
        return D3DBLEND_SRCCOLOR;
    case Factor::InvertedSourceColor:
        return D3DBLEND_INVSRCCOLOR;
    case Factor::DestinationColor:
        return D3DBLEND_DESTCOLOR;
    case Factor::InvertedDestinationColor:
        return D3DBLEND_INVDESTCOLOR;
    case Factor::SourceAlpha:
        return D3DBLEND_SRCALPHA;
    case Factor::InvertedSourceAlpha:
        return D3DBLEND_INVSRCALPHA;
    case Factor::DestinationAlpha:
        return D3DBLEND_DESTALPHA;
    case Factor::InvertedDestinationAlpha:
        return D3DBLEND_INVDESTALPHA;
    case Factor::SourceAlphaSaturate:
        return D3DBLEND_SRCALPHASAT;
    default:
        throwInvalidArgument( "'factor' is invalid" );
    }
}

BlendingTechnique::Pointer BlendingTechnique::create(
    const Description &description )
{
    return std::make_shared<BlendingTechniqueDx9>( description );
}

}
