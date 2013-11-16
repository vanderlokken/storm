#include <storm/blending_technique.h>

namespace storm {

BlendingTechnique::Pointer BlendingTechnique::getDefault() {
    Description description;
    description.operation = Operation::Addition;
    description.sourceFactor = Factor::SourceAlpha;
    description.destinationFactor = Factor::InvertedSourceAlpha;

    static const BlendingTechnique::Pointer technique = create( description );
    return technique;
}

}