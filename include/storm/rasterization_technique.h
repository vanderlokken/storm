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
        bool depthClippingEnabled;
        int depthBias;
        float slopeScaleDepthBias;
        size_t clippingDistanceArraySize;
    };

    static RasterizationTechnique::Pointer create( const Description& );
    static RasterizationTechnique::Pointer getDefault();
    static RasterizationTechnique::Pointer getDefaultWithoutCulling();
    static RasterizationTechnique::Pointer getDefaultWithoutDepthClipping();

    virtual ~RasterizationTechnique() = default;

    virtual const Description& getDescription() const = 0;
};

}
