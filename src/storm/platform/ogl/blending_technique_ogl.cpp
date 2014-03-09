#include <storm/platform/ogl/blending_technique_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

BlendingTechniqueOgl::BlendingTechniqueOgl( const Description &description )
    : _description( description ),
      _operation( convertOperation(description.operation) ),
      _sourceFactor( convertFactor(description.sourceFactor) ),
      _destinationFactor( convertFactor(description.destinationFactor) )
{
    return;
}

const BlendingTechnique::Description& BlendingTechniqueOgl::getDescription() const {
    return _description;
}

GLenum BlendingTechniqueOgl::getOperation() const {
    return _operation;
}

GLenum BlendingTechniqueOgl::getSourceFactor() const {
    return _sourceFactor;
}

GLenum BlendingTechniqueOgl::getDestinationFactor() const {
    return _destinationFactor;
}

GLenum BlendingTechniqueOgl::convertOperation( Operation operation ) {
    switch( operation ) {
    case Operation::Addition:
        return GL_FUNC_ADD;
    case Operation::Subtraction:
        return GL_FUNC_SUBTRACT;
    case Operation::NegativeSubtraction:
        return GL_FUNC_REVERSE_SUBTRACT;
    case Operation::Minimum:
        return GL_MIN;
    case Operation::Maximum:
        return GL_MAX;
    default:
        throwInvalidArgument( "'operation' is invalid" );
    }
}

GLenum BlendingTechniqueOgl::convertFactor( Factor factor ) {
    switch( factor ) {
    case Factor::Zero:
        return GL_ZERO;
    case Factor::One:
        return GL_ONE;
    case Factor::SourceColor:
        return GL_SRC_COLOR;
    case Factor::InvertedSourceColor:
        return GL_ONE_MINUS_SRC_COLOR;
    case Factor::DestinationColor:
        return GL_DST_COLOR;
    case Factor::InvertedDestinationColor:
        return GL_ONE_MINUS_DST_COLOR;
    case Factor::SourceAlpha:
        return GL_SRC_ALPHA;
    case Factor::InvertedSourceAlpha:
        return GL_ONE_MINUS_SRC_ALPHA;
    case Factor::DestinationAlpha:
        return GL_DST_ALPHA;
    case Factor::InvertedDestinationAlpha:
        return GL_ONE_MINUS_DST_ALPHA;
    case Factor::SourceAlphaSaturate:
        return GL_SRC_ALPHA_SATURATE;
    default:
        throwInvalidArgument( "'factor' is invalid" );
    }
}

BlendingTechnique::Pointer BlendingTechnique::create(
    const Description &description )
{
    return std::make_shared< BlendingTechniqueOgl >( description );
}

}
