#pragma once

#include <memory>
#include <string>

#include <storm/buffer.h>
#include <storm/vertex_format.h>

namespace storm {

class Mesh {
public:
    typedef std::shared_ptr<Mesh> Pointer;

    enum class TriangleTopology {
        List,
        Strip
    };

    struct Description {
        Buffer::Pointer indexBuffer;
        Buffer::Pointer vertexBuffer;
        VertexFormat::Pointer vertexFormat;
        TriangleTopology triangleTopology;
    };

    static Pointer create( const Description& );
    static Pointer load( const std::string &filename );

    virtual ~Mesh() { }

    virtual const Description& getDescription() const = 0;
};

}
