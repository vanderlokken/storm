#include <storm/rasterization_technique.h>

namespace storm {

RasterizationTechnique::Pointer RasterizationTechnique::getDefault() {
    Description description;
    description.cullMode = CullBackFaces;
    description.fillMode = FillSolid;
    description.rectangleClippingEnabled = false;
    description.depthBias = 0;
    description.slopeScaleDepthBias = 0;

    static const RasterizationTechnique::Pointer technique = create( description );
    return technique;
}

}