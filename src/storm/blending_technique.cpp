#include <storm/blending_technique.h>

namespace storm {

BlendingTechnique::Pointer BlendingTechnique::getDefault() {
    Description description;
    description.colorEquation.operation = Operation::Addition;
    description.colorEquation.sourceFactor = Factor::SourceAlpha;
    description.colorEquation.destinationFactor = Factor::InvertedSourceAlpha;
    description.alphaEquation = description.colorEquation;

    static const BlendingTechnique::Pointer technique = create( description );
    return technique;
}

}