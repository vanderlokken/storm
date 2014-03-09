#pragma once

#include <memory>

namespace storm {

class RasterizationTechnique {
public:
    typedef std::shared_ptr<RasterizationTechnique> Pointer;

    enum class CullMode {
        Nothing,
        FrontFaces,
        BackFaces
    };

    enum class FillMode {
        Solid,
        Wireframe
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

    virtual const Description& getDescription() const = 0;
};

}
