#pragma once

#include <memory>
#include <string>

#include "Noexcept.h"

namespace storm {

class IndexBuffer;
class VertexBuffer;

class Mesh {
public:
    enum TriangleTopology {
        TriangleTopologyList,
        TriangleTopologyStrip
    };

    struct Description {
        TriangleTopology triangleTopology;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };

    static std::shared_ptr<Mesh> create( const Description& );
    static std::shared_ptr<Mesh> load( const std::string &filename );

    virtual ~Mesh() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
