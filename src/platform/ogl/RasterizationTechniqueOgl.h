#pragma once

#include "CoreTypesOgl.h"
#include "RasterizationTechnique.h"

namespace storm {

class RasterizationTechniqueOgl : public RasterizationTechnique {
public:
    RasterizationTechniqueOgl( const Description& );

    virtual const Description& getDescription() const noexcept;

    GLenum getCullMode() const noexcept;
    GLenum getFillMode() const noexcept;

private:
    static GLenum convertCullMode( CullMode );
    static GLenum convertFillMode( FillMode );

    Description _description;
    GLenum _cullMode;
    GLenum _fillMode;
};

}
