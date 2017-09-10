#include <storm/output_technique.h>

namespace storm {

OutputTechnique::Pointer OutputTechnique::getDefault() {
    DepthTest depthTest;
    depthTest.passCondition = Condition::Less;

    Description description;
    description.depthTest = depthTest;
    description.writeDepthValues = true;

    static const OutputTechnique::Pointer technique = create( description );
    return technique;
}

OutputTechnique::Pointer OutputTechnique::getDefaultWithoutDepthOutput() {
    Description description = getDefault()->getDescription();
    description.writeDepthValues = false;

    static const OutputTechnique::Pointer technique = create( description );
    return technique;
}

OutputTechnique::Pointer OutputTechnique::getDefaultWithoutDepthInputOutput() {
    Description description = getDefault()->getDescription();
    description.depthTest = std::nullopt;
    description.writeDepthValues = false;

    static const OutputTechnique::Pointer technique = create( description );
    return technique;
}

}
