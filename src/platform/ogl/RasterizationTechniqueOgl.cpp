#include "RasterizationTechniqueOgl.h"

#include "ConstantsOgl.h"
#include "Exception.h"

namespace storm {

RasterizationTechniqueOgl::RasterizationTechniqueOgl( const Description &description )
    : _description( description ),
      _cullMode( convertCullMode(description.cullMode) ),
      _fillMode( convertFillMode(description.fillMode) )
{
    return;
}

const RasterizationTechnique::Description& RasterizationTechniqueOgl::getDescription() const noexcept {
    return _description;
}

GLenum RasterizationTechniqueOgl::getCullMode() const noexcept {
    return _cullMode;
}

GLenum RasterizationTechniqueOgl::getFillMode() const noexcept {
    return _fillMode;
}

GLenum RasterizationTechniqueOgl::convertCullMode( CullMode cullMode ) {
    GLenum result;

    switch( cullMode ) {
    case CullNothing:

        // GL_NONE is not a valid argument for ::glCullFace. This value just
        // indicates that ::glDisable( GL_CULL_FACE ) should be called instead
        // of ::glCullFace.

        result = GL_NONE;
        break;

    case CullFrontFaces:
        result = GL_FRONT;
        break;

    case CullBackFaces:
        result = GL_BACK;
        break;

    default:
        throwInvalidArgument( "'cullMode' is invalid" );
    }
    return result;
}

GLenum RasterizationTechniqueOgl::convertFillMode( FillMode fillMode ) {
    GLenum result;

    switch( fillMode ) {
    case FillSolid:
        result = GL_FILL;
        break;

    case FillWireframe:
        result = GL_LINE;
        break;

    default:
        throwInvalidArgument( "'fillMode' is invalid" );
    }
    return result;
}

std::shared_ptr<RasterizationTechnique> RasterizationTechnique::create( const Description &description ) {
    return std::make_shared< RasterizationTechniqueOgl >( description );
}

}