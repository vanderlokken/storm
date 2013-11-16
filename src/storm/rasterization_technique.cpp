#include <storm/rasterization_technique.h>

namespace storm {

RasterizationTechnique::Pointer RasterizationTechnique::getDefault() {
    Description description;
    description.cullMode = CullMode::BackFaces;
    description.fillMode = FillMode::Solid;
    description.rectangleClippingEnabled = false;
    description.depthBias = 0;
    description.slopeScaleDepthBias = 0;

    static const RasterizationTechnique::Pointer technique = create( description );
    return technique;
}

}