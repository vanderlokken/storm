#pragma once

#include <memory>
#include <string>

#include <storm/index_buffer.h>
#include <storm/noexcept.h>
#include <storm/vertex_buffer.h>

namespace storm {

class Mesh {
public:
    typedef std::shared_ptr<Mesh> Pointer;

    enum TriangleTopology {
        TriangleTopologyList,
        TriangleTopologyStrip
    };

    struct Description {
        TriangleTopology triangleTopology;
        VertexBuffer::Pointer vertexBuffer;
        IndexBuffer::Pointer indexBuffer;
    };

    static Mesh::Pointer create( const Description& );
    static Mesh::Pointer load( const std::string &filename );

    virtual ~Mesh() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
