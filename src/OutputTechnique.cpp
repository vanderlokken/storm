#include "OutputTechnique.h"

namespace storm {

std::shared_ptr<OutputTechnique> OutputTechnique::getDefault() {
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
    
    static const std::shared_ptr<OutputTechnique> technique( OutputTechnique::create(description) );
    return technique;
}

}