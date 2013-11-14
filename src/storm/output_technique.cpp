#include <storm/output_technique.h>

namespace storm {

OutputTechnique::Pointer OutputTechnique::getDefault() {
    Description description;
    description.depthTest.enabled = true;
    description.depthTest.passCondition = ConditionLess;

    description.stencilTest.enabled = false;
    description.stencilTest.referenceValue = 0;
    description.stencilTest.mask = ~0U;

    description.stencilTest.algorithmForFrontFaces.passCondition = ConditionTrue;
    description.stencilTest.algorithmForFrontFaces.operationOnStencilTestFail = StencilOperationKeep;
    description.stencilTest.algorithmForFrontFaces.operationOnDepthTestFail = StencilOperationKeep;
    description.stencilTest.algorithmForFrontFaces.operationOnDepthTestPass = StencilOperationKeep;

    description.stencilTest.algorithmForBackFaces.passCondition = ConditionTrue;
    description.stencilTest.algorithmForBackFaces.operationOnStencilTestFail = StencilOperationKeep;
    description.stencilTest.algorithmForBackFaces.operationOnDepthTestFail = StencilOperationKeep;
    description.stencilTest.algorithmForBackFaces.operationOnDepthTestPass = StencilOperationKeep;

    description.writeDepthValues = true;

    static const OutputTechnique::Pointer technique = create( description );
    return technique;
}

}