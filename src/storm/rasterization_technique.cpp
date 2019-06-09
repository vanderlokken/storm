#include <storm/rasterization_technique.h>

namespace storm {

RasterizationTechnique::Pointer RasterizationTechnique::getDefault() {
    Description description;
    description.cullMode = CullMode::BackFaces;
    description.fillMode = FillMode::Solid;
    description.rectangleClippingEnabled = false;
    description.depthClippingEnabled = true;
    description.depthBias = 0;
    description.slopeScaleDepthBias = 0;
    description.clippingDistanceArraySize = 0;

    static const RasterizationTechnique::Pointer technique =
        create( description );
    return technique;
}

RasterizationTechnique::Pointer
RasterizationTechnique::getDefaultWithoutCulling() {
    Description description = getDefault()->getDescription();
    description.cullMode = CullMode::Nothing;

    static const RasterizationTechnique::Pointer technique =
        create( description );
    return technique;
}

RasterizationTechnique::Pointer
RasterizationTechnique::getDefaultWithoutDepthClipping() {
    Description description = getDefault()->getDescription();
    description.depthClippingEnabled = false;

    static const RasterizationTechnique::Pointer technique =
        create( description );
    return technique;
}

}
