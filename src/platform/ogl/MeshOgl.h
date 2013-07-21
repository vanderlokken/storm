#ifndef storm_MeshOgl_h
#define storm_MeshOgl_h

#include "CoreTypesOgl.h"
#include "HandleOgl.h"
#include "Mesh.h"
#include "Vertex.h"

namespace storm {

class MeshHandleOgl : public HandleOgl {
public:
    MeshHandleOgl();
    ~MeshHandleOgl() noexcept;
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

#endif
