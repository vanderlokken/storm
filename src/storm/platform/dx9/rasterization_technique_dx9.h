#pragma once

#include <storm/platform/dx9/core_types_dx9.h>
#include <storm/rasterization_technique.h>

// This definition is provided only for the readability improvement
typedef D3DCULL D3DCULLMODE;

namespace storm {

class RasterizationTechniqueDx9 : public RasterizationTechnique {
public:
    RasterizationTechniqueDx9( const Description& );

    virtual const Description& getDescription() const noexcept;

    D3DCULLMODE getCullMode() const noexcept;
    D3DFILLMODE getFillMode() const noexcept;

private:
    static D3DCULLMODE convertCullMode( CullMode );
    static D3DFILLMODE convertFillMode( FillMode );

    Description _description;
    D3DCULLMODE _cullMode;
    D3DFILLMODE _fillMode;
};

}
