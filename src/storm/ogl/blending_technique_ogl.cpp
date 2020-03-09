#include <storm/ogl/blending_technique_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

BlendingTechniqueOgl::BlendingTechniqueOgl( const Description &description ) :
    _description( description )
{
    _colorEquation.operation =
        convertOperation( description.colorEquation.operation );
    _colorEquation.sourceFactor =
        convertFactor( description.colorEquation.sourceFactor );
    _colorEquation.destinationFactor =
        convertFactor( description.colorEquation.destinationFactor );

    _alphaEquation.operation =
        convertOperation( description.alphaEquation.operation );
    _alphaEquation.sourceFactor =
        convertFactor( description.alphaEquation.sourceFactor );
    _alphaEquation.destinationFactor =
        convertFactor( description.alphaEquation.destinationFactor );
}

const BlendingTechnique::Description& BlendingTechniqueOgl::getDescription() const {
    return _description;
}

BlendingTechniqueOgl::EquationOgl
BlendingTechniqueOgl::getColorEquation() const {
    return _colorEquation;
}

BlendingTechniqueOgl::EquationOgl
BlendingTechniqueOgl::getAlphaEquation() const {
    return _alphaEquation;
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
        storm_assert_unreachable( "Unexpected operation value" );
        return 0;
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
        storm_assert_unreachable( "Unexpected factor value" );
        return 0;
    }
}

BlendingTechnique::Pointer BlendingTechnique::create(
    const Description &description )
{
    return std::make_shared< BlendingTechniqueOgl >( description );
}

}
