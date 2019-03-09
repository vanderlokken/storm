#pragma once

#include <storm/mesh.h>
#include <storm/platform/ogl/handle_ogl.h>

namespace storm {

class VertexArrayHandleOgl : public HandleOgl {
public:
    VertexArrayHandleOgl();
    ~VertexArrayHandleOgl();
};

class MeshOgl : public Mesh {
public:
    MeshOgl( const Description& );

    const Description& getDescription() const override;

    GLenum getPrimitiveTopology() const;
    const VertexArrayHandleOgl& getHandle() const;

    static GLenum convertPrimitiveTopology( PrimitiveTopology );

private:
    Description _description;
    GLenum _primitiveTopology;
    VertexArrayHandleOgl _handle;
};

}
