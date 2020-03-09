#include <storm/ogl/output_technique_ogl.h>

#include <storm/throw_exception.h>
#include <storm/ogl/condition_ogl.h>

namespace storm {

OutputTechniqueOgl::OutputTechniqueOgl(
        const OutputTechnique::Description &description ) :
    _description( description )
{
    if( description.depthTest ) {
        _nativeDescription.depthTest =
            convertDepthTestDescription( *description.depthTest );
    }
    if( description.stencilTest ) {
        _nativeDescription.stencilTest =
            convertStencilTestDescription( *description.stencilTest );
    }
    _nativeDescription.writeDepthValues = description.writeDepthValues;
}

const OutputTechnique::Description&
    OutputTechniqueOgl::getDescription() const
{
    return _description;
}

const OutputTechniqueOgl::Description&
    OutputTechniqueOgl::getNativeDescription() const
{
    return _nativeDescription;
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
        storm_assert_unreachable( "Unexpected operation value" );
        return 0;
    }
}

OutputTechniqueOgl::DepthTest OutputTechniqueOgl::convertDepthTestDescription(
    const OutputTechnique::DepthTest &description )
{
    OutputTechniqueOgl::DepthTest result;

    result.passCondition = convertCondition( description.passCondition );

    return result;
}

OutputTechniqueOgl::StencilTest OutputTechniqueOgl::convertStencilTestDescription(
    const OutputTechnique::StencilTest &description )
{
    OutputTechniqueOgl::StencilTest result;

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

    result.referenceValue = description.referenceValue;
    result.mask = description.mask;

    result.algorithmForFrontFaces =
        convertAlgorithm( description.algorithmForFrontFaces );
    result.algorithmForBackFaces =
        convertAlgorithm( description.algorithmForBackFaces );

    return result;
}

OutputTechnique::Pointer OutputTechnique::create(
    const Description &description )
{
    return std::make_shared<OutputTechniqueOgl>( description );
}

}
