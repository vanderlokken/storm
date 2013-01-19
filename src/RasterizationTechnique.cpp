#include "RasterizationTechnique.h"

namespace storm {

std::shared_ptr<RasterizationTechnique> RasterizationTechnique::getDefault() {
    Description description;
    description.cullMode = CullBackFaces;
    description.fillMode = FillSolid;
    description.rectangleClippingEnabled = false;
    description.depthBias = 0;
    description.slopeScaleDepthBias = 0;

    static const std::shared_ptr<RasterizationTechnique> technique( create(description) );
    return technique;
}

}