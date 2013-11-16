#include <storm/platform/dx9/rasterization_technique_dx9.h>

#include <storm/exception.h>

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
    switch( cullMode ) {
    case CullMode::Nothing:
        return D3DCULL_NONE;
    case CullMode::FrontFaces:
        return D3DCULL_CW;
    case CullMode::BackFaces:
        return D3DCULL_CCW;
    default:
        throwInvalidArgument( "'cullMode' is invalid" );
    }
}

D3DFILLMODE RasterizationTechniqueDx9::convertFillMode( FillMode fillMode ) {
    switch( fillMode ) {
    case FillMode::Solid:
        return D3DFILL_SOLID;
    case FillMode::Wireframe:
        return D3DFILL_WIREFRAME;
    default:
        throwInvalidArgument( "'fillMode' is invalid" );
    }
}

RasterizationTechnique::Pointer RasterizationTechnique::create( const Description &description ) {
    return std::make_shared<RasterizationTechniqueDx9>( description );
}

}