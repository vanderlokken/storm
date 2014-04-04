#pragma once

#include <storm/mesh.h>
#include <storm/platform/ogl/handle_ogl.h>

namespace storm {

class MeshHandleOgl : public HandleOgl {
public:
    MeshHandleOgl();
    ~MeshHandleOgl();
};

class MeshOgl : public Mesh {
public:
    MeshOgl( const Description& );

    virtual const Description& getDescription() const;

    GLenum getPrimitiveTopology() const;
    const MeshHandleOgl& getHandle() const;

private:
    static GLenum convertPrimitiveTopology( PrimitiveTopology );

    Description _description;
    GLenum _primitiveTopology;
    MeshHandleOgl _handle;
};

}
