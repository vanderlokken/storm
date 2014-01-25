#include <storm/platform/ogl/output_technique_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

OutputTechniqueOgl::OutputTechniqueOgl(
    const OutputTechnique::Description &description )
        : _description( description )
{
    _nativeDescription.depthTest =
        convertDepthTestDescription( description.depthTest );
    _nativeDescription.stencilTest =
        convertStencilTestDescription( description.stencilTest );
    _nativeDescription.writeDepthValues = description.writeDepthValues;
}

const OutputTechnique::Description&
    OutputTechniqueOgl::getDescription() const noexcept
{
    return _description;
}

const OutputTechniqueOgl::Description&
    OutputTechniqueOgl::getNativeDescription() const noexcept
{
    return _nativeDescription;
}

GLenum OutputTechniqueOgl::convertCondition( Condition condition ) {
    switch( condition ) {
    case Condition::False:
        return GL_NEVER;
    case Condition::True:
        return GL_ALWAYS;
    case Condition::Less:
        return GL_LESS;
    case Condition::LessOrEqual:
        return GL_LEQUAL;
    case Condition::Greater:
        return GL_GREATER;
    case Condition::GreaterOrEqual:
        return GL_GEQUAL;
    case Condition::Equal:
        return GL_EQUAL;
    case Condition::NotEqual:
        return GL_NOTEQUAL;
    default:
        throwInvalidArgument( "'condition' is invalid" );
    }
}

GLenum OutputTechniqueOgl::convertStencilOperation(
    StencilOperation operation )
{
    switch( operation ) {
    case StencilOperation::Zero:
        return GL_ZERO;
    case StencilOperation::Keep:
        return GL_KEEP;
    case StencilOperation::Replace:
        return GL_REPLACE;
    case StencilOperation::IncrementTruncate:
        return GL_INCR_WRAP;
    case StencilOperation::DecrementTruncate:
        return GL_DECR_WRAP;
    case StencilOperation::Increment:
        return GL_INCR;
    case StencilOperation::Decrement:
        return GL_DECR;
    case StencilOperation::Invert:
        return GL_INVERT;
    default:
        throwInvalidArgument( "'operation' is invalid" );
    }
}

OutputTechniqueOgl::DepthTest OutputTechniqueOgl::convertDepthTestDescription(
    const OutputTechnique::DepthTest &description )
{
    OutputTechniqueOgl::DepthTest result;
    result.enabled = description.enabled;

    if( description.enabled )
        result.passCondition = convertCondition( description.passCondition );

    return result;
}

OutputTechniqueOgl::StencilTest OutputTechniqueOgl::convertStencilTestDescription(
    const OutputTechnique::StencilTest &description )
{
    OutputTechniqueOgl::StencilTest result;
    result.enabled = description.enabled;

    auto convertAlgorithm = []( OutputTechnique::StencilTest::Algorithm algorithm ) {
        StencilTest::Algorithm result;

        result.passCondition = convertCondition( algorithm.passCondition );
        result.operationOnStencilTestFail =
            convertStencilOperation( algorithm.operationOnStencilTestFail );
        result.operationOnDepthTestFail =
            convertStencilOperation( algorithm.operationOnDepthTestFail );
        result.operationOnDepthTestPass =
            convertStencilOperation( algorithm.operationOnDepthTestPass );

        return result;
    };

    if( description.enabled ) {
        result.referenceValue = description.referenceValue;
        result.mask = description.mask;

        result.algorithmForFrontFaces =
            convertAlgorithm( description.algorithmForFrontFaces );
        result.algorithmForBackFaces =
            convertAlgorithm( description.algorithmForBackFaces );
    }

    return result;
}

OutputTechnique::Pointer OutputTechnique::create( const Description &description ) {
    return std::make_shared< OutputTechniqueOgl >( description );
}

}
