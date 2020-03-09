#pragma once

#include <storm/ogl/api_ogl.h>
#include <storm/rasterization_technique.h>

namespace storm {

class RasterizationTechniqueOgl : public RasterizationTechnique {
public:
    RasterizationTechniqueOgl( const Description& );

    const Description& getDescription() const override;

    GLenum getCullMode() const;
    GLenum getFillMode() const;

private:
    static GLenum convertCullMode( CullMode );
    static GLenum convertFillMode( FillMode );

    Description _description;
    GLenum _cullMode;
    GLenum _fillMode;
};

}
