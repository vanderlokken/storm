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
    D3DBLENDOP result;

    switch( operation ) {
    case OperationAddition:
        result = D3DBLENDOP_ADD;
        break;

    case OperationSubtraction:
        result = D3DBLENDOP_SUBTRACT;
        break;

    case OperationNegativeSubtraction:
        result = D3DBLENDOP_REVSUBTRACT;
        break;

    case OperationMinimum:
        result = D3DBLENDOP_MIN;
        break;

    case OperationMaximum:
        result = D3DBLENDOP_MAX;
        break;

    default:
        throwInvalidArgument( "'operation' is invalid" );
    }
    return result;
}

D3DBLEND BlendingTechniqueDx9::convertFactor( Factor factor ) {
    D3DBLEND result;

    switch( factor ) {
    case FactorZero:
        result = D3DBLEND_ZERO;
        break;

    case FactorOne:
        result = D3DBLEND_ONE;
        break;

    case FactorSourceColor:
        result = D3DBLEND_SRCCOLOR;
        break;

    case FactorInvertedSourceColor:
        result = D3DBLEND_INVSRCCOLOR;
        break;

    case FactorDestinationColor:
        result = D3DBLEND_DESTCOLOR;
        break;

    case FactorInvertedDestinationColor:
        result = D3DBLEND_INVDESTCOLOR;
        break;

    case FactorSourceAlpha:
        result = D3DBLEND_SRCALPHA;
        break;

    case FactorInvertedSourceAlpha:
        result = D3DBLEND_INVSRCALPHA;
        break;

    case FactorDestinationAlpha:
        result = D3DBLEND_DESTALPHA;
        break;

    case FactorInvertedDestinationAlpha:
        result = D3DBLEND_INVDESTALPHA;
        break;

    case FactorSourceAlphaSaturate:
        result = D3DBLEND_SRCALPHASAT;
        break;

    default:
        throwInvalidArgument( "'factor' is invalid" );
    }
    return result;
}

std::shared_ptr<BlendingTechnique> BlendingTechnique::create( const Description &description ) {
    return std::make_shared<BlendingTechniqueDx9>( description );
}

}