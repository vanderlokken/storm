#pragma once

#include <storm/mesh.h>
#include <storm/platform/dx9/core_types_dx9.h>

namespace storm {

class MeshDx9 : public Mesh {
public:
    MeshDx9( const Description& );

    virtual const Description& getDescription() const noexcept;

    D3DPRIMITIVETYPE getTriangleTopology() const noexcept;
                UINT getTriangleCount() const noexcept;

private:
    static D3DPRIMITIVETYPE convertTriangleTopology( TriangleTopology );

    Description _description;
    D3DPRIMITIVETYPE _triangleTopology;
};

}
