#include <storm/output_technique.h>

namespace storm {

OutputTechnique::Pointer OutputTechnique::getDefault() {
    Description description;
    description.depthTest.enabled = true;
    description.depthTest.passCondition = Condition::Less;

    description.stencilTest.enabled = false;
    description.stencilTest.referenceValue = 0;
    description.stencilTest.mask = ~0U;

    description.stencilTest.algorithmForFrontFaces.passCondition = Condition::True;
    description.stencilTest.algorithmForFrontFaces.operationOnStencilTestFail = StencilOperation::Keep;
    description.stencilTest.algorithmForFrontFaces.operationOnDepthTestFail = StencilOperation::Keep;
    description.stencilTest.algorithmForFrontFaces.operationOnDepthTestPass = StencilOperation::Keep;

    description.stencilTest.algorithmForBackFaces.passCondition = Condition::True;
    description.stencilTest.algorithmForBackFaces.operationOnStencilTestFail = StencilOperation::Keep;
    description.stencilTest.algorithmForBackFaces.operationOnDepthTestFail = StencilOperation::Keep;
    description.stencilTest.algorithmForBackFaces.operationOnDepthTestPass = StencilOperation::Keep;

    description.writeDepthValues = true;

    static const OutputTechnique::Pointer technique = create( description );
    return technique;
}

}