#include <storm/blending_technique.h>

namespace storm {

BlendingTechnique::Pointer BlendingTechnique::getDefault() {
    Description description;
    description.operation = OperationAddition;
    description.sourceFactor = FactorSourceAlpha;
    description.destinationFactor = FactorInvertedSourceAlpha;

    static const BlendingTechnique::Pointer technique = create( description );
    return technique;
}

}