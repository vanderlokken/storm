#ifndef storm_RasterizationTechnique_h
#define storm_RasterizationTechnique_h

#include <memory>

#include "Noexcept.h"

namespace storm {

class RasterizationTechnique {
public:
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
    
    static std::shared_ptr<RasterizationTechnique> create( const Description& );
    static std::shared_ptr<RasterizationTechnique> getDefault();
    
    virtual ~RasterizationTechnique() noexcept { }
    
    virtual const Description& getDescription() const noexcept = 0;
};

}

#endif