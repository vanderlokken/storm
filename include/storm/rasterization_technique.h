#pragma once

#include <memory>

#include <storm/noexcept.h>

namespace storm {

class RasterizationTechnique {
public:
    typedef std::shared_ptr<RasterizationTechnique> Pointer;

    enum CullMode {
        CullNothing,
        CullFrontFaces,
        CullBackFaces
    };

    enum FillMode {
        FillSolid,
        FillWireframe
    };

    struct Description {
        CullMode cullMode;
        FillMode fillMode;
        bool rectangleClippingEnabled;
        int depthBias;
        float slopeScaleDepthBias;
    };

    static RasterizationTechnique::Pointer create( const Description& );
    static RasterizationTechnique::Pointer getDefault();

    virtual ~RasterizationTechnique() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
