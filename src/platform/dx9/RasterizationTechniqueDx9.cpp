#include "RasterizationTechniqueDx9.h"

#include "Exception.h"

namespace storm {

RasterizationTechniqueDx9::RasterizationTechniqueDx9( const Description &description )
    : _description( description ),
      _cullMode( convertCullMode(description.cullMode) ),
      _fillMode( convertFillMode(description.fillMode) )
{
    return;
}

const RasterizationTechnique::Description& RasterizationTechniqueDx9::getDescription() const noexcept {
    return _description;
}

D3DCULLMODE RasterizationTechniqueDx9::getCullMode() const noexcept {
    return _cullMode;
}

D3DFILLMODE RasterizationTechniqueDx9::getFillMode() const noexcept {
    return _fillMode;
}

D3DCULLMODE RasterizationTechniqueDx9::convertCullMode( CullMode cullMode ) {
    D3DCULLMODE result;

    switch( cullMode ) {
    case CullNothing:
        result = D3DCULL_NONE;
        break;

    case CullFrontFaces:
        result = D3DCULL_CW;
        break;

    case CullBackFaces:
        result = D3DCULL_CCW;
        break;

    default:
        throwInvalidArgument( "'cullMode' is invalid" );
    }
    return result;
}

D3DFILLMODE RasterizationTechniqueDx9::convertFillMode( FillMode fillMode ) {
    D3DFILLMODE result;

    switch( fillMode ) {
    case FillSolid:
        result = D3DFILL_SOLID;
        break;

    case FillWireframe:
        result = D3DFILL_WIREFRAME;
        break;

    default:
        throwInvalidArgument( "'fillMode' is invalid" );
    }
    return result;
}

std::shared_ptr<RasterizationTechnique> RasterizationTechnique::create( const Description &description ) {
    return std::make_shared<RasterizationTechniqueDx9>( description );
}

}