#pragma once

#include <storm/mesh.h>
#include <storm/ogl/gpu_context_ogl.h>
#include <storm/ogl/handle_ogl.h>

namespace storm {

using VertexArrayHandleOgl =
    HandleOgl<GlGenVertexArrays, GlDeleteVertexArrays>;

class MeshOgl : public Mesh {
public:
    MeshOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description );

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
