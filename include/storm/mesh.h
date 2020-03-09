#pragma once

#include <iosfwd>
#include <memory>
#include <string_view>

#include <storm/buffer.h>
#include <storm/vertex_format.h>

namespace storm {

class Mesh {
public:
    using Pointer = std::shared_ptr<Mesh>;

    enum class PrimitiveTopology {
        PointList,
        LineList,
        LineStrip,
        TriangleList,
        TriangleStrip
    };

    // The allowed values for the 'indexSize' field are 2 and 4.
    struct Description {
        Buffer::Pointer indexBuffer;
        Buffer::Pointer vertexBuffer;
        VertexFormat::Pointer vertexFormat;
        PrimitiveTopology primitiveTopology;
        size_t indexSize;
    };

    static Pointer create( const Description& );
    static Pointer load( std::istream &stream );
    static Pointer load( std::string_view filename );

    virtual ~Mesh() = default;

    virtual const Description& getDescription() const = 0;
};

}
