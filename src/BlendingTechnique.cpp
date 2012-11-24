#include "BlendingTechnique.h"

namespace storm {

std::shared_ptr<BlendingTechnique> BlendingTechnique::getDefault() {
    Description description;
    description.operation = OperationAddition;
    description.sourceFactor = FactorSourceAlpha;
    description.destinationFactor = FactorInvertedSourceAlpha;
    
    static const std::shared_ptr<BlendingTechnique> technique( BlendingTechnique::create(description) );
    return technique;
}

}