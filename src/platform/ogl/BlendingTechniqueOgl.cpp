#include "BlendingTechniqueOgl.h"

#include "ConstantsOgl.h"
#include "Exception.h"

namespace storm {

BlendingTechniqueOgl::BlendingTechniqueOgl( const Description &description )
    : _description( description ),
      _operation( convertOperation(description.operation) ),
      _sourceFactor( convertFactor(description.sourceFactor) ),
      _destinationFactor( convertFactor(description.destinationFactor) )
{
    return;
}

const BlendingTechnique::Description& BlendingTechniqueOgl::getDescription() const noexcept {
    return _description;
}

GLenum BlendingTechniqueOgl::getOperation() const noexcept {
    return _operation;
}

GLenum BlendingTechniqueOgl::getSourceFactor() const noexcept {
    return _sourceFactor;
}

GLenum BlendingTechniqueOgl::getDestinationFactor() const noexcept {
    return _destinationFactor;
}

GLenum BlendingTechniqueOgl::convertOperation( Operation operation ) {
    GLenum result;

    switch( operation ) {
    case OperationAddition:
        result = GL_FUNC_ADD;
        break;

    case OperationSubtraction:
        result = GL_FUNC_SUBTRACT;
        break;

    case OperationNegativeSubtraction:
        result = GL_FUNC_REVERSE_SUBTRACT;
        break;

    case OperationMinimum:
        result = GL_MIN;
        break;

    case OperationMaximum:
        result = GL_MAX;
        break;

    default:
        throwInvalidArgument( "'operation' is invalid" );
    }
    return result;
}

GLenum BlendingTechniqueOgl::convertFactor( Factor factor ) {
    GLenum result;

    switch( factor ) {
    case FactorZero:
        result = GL_ZERO;
        break;

    case FactorOne:
        result = GL_ONE;
        break;

    case FactorSourceColor:
        result = GL_SRC_COLOR;
        break;

    case FactorInvertedSourceColor:
        result = GL_ONE_MINUS_SRC_COLOR;
        break;

    case FactorDestinationColor:
        result = GL_DST_COLOR;
        break;

    case FactorInvertedDestinationColor:
        result = GL_ONE_MINUS_DST_COLOR;
        break;

    case FactorSourceAlpha:
        result = GL_SRC_ALPHA;
        break;

    case FactorInvertedSourceAlpha:
        result = GL_ONE_MINUS_SRC_ALPHA;
        break;

    case FactorDestinationAlpha:
        result = GL_DST_ALPHA;
        break;

    case FactorInvertedDestinationAlpha:
        result = GL_ONE_MINUS_DST_ALPHA;
        break;

    case FactorSourceAlphaSaturate:
        result = GL_SRC_ALPHA_SATURATE;
        break;

    default:
        throwInvalidArgument( "'factor' is invalid" );
    }
    return result;
}

std::shared_ptr<BlendingTechnique> BlendingTechnique::create( const Description &description ) {
    return std::make_shared< BlendingTechniqueOgl >( description );
}

}