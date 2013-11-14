#pragma once

#include <storm/mesh.h>
#include <storm/vertex.h>
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

    virtual const Description& getDescription() const noexcept;

    GLenum getTriangleTopology() const noexcept;
    const MeshHandleOgl& getHandle() const noexcept;

private:
    void setVertexAttributes();

    static GLenum convertTriangleTopology( TriangleTopology );

    struct VertexAttributeFormat {
        GLint componentCount;
        GLenum componentType;
        GLboolean componentNormalized;
    };

    static VertexAttributeFormat convertVertexAttributeFormat( Vertex::Attribute::Format );

    Description _description;
    GLenum _triangleTopology;
    MeshHandleOgl _handle;
};

}
