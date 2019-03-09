#pragma once

#include <iosfwd>
#include <memory>
#include <string_view>

#include <storm/buffer.h>
#include <storm/vertex_format.h>

namespace storm {

class Mesh {
public:
    typedef std::shared_ptr<Mesh> Pointer;

    enum class PrimitiveTopology {
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip
    };

    struct Description {
        Buffer::Pointer indexBuffer;
        Buffer::Pointer vertexBuffer;
        VertexFormat::Pointer vertexFormat;
        PrimitiveTopology primitiveTopology;
    };

    static Pointer create( const Description& );
    static Pointer load( std::istream &stream );
    static Pointer load( std::string_view filename );

    // Returns a mesh that covers entire screen in normalized device
    // coordinates. Vertices have no attributes besides positions.
    static Pointer getFullscreen();

    virtual ~Mesh() { }

    virtual const Description& getDescription() const = 0;
};

}
