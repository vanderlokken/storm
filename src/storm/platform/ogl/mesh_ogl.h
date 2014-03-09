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

    GLenum getTriangleTopology() const;
    const MeshHandleOgl& getHandle() const;

private:
    static GLenum convertTriangleTopology( TriangleTopology );

    Description _description;
    GLenum _triangleTopology;
    MeshHandleOgl _handle;
};

}
