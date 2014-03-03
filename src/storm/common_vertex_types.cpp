#include <storm/common_vertex_types.h>

namespace storm {

typedef VertexFormat::Attribute VertexAttribute;

VertexFormat::Pointer TexturedVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::TextureCoordinates,
            VertexAttribute::Format::Vector2Float
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes} );
    return format;
}

VertexFormat::Pointer ColoredVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::Color,
            VertexAttribute::Format::Vector4Uint8Normalized
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes} );
    return format;
}

VertexFormat::Pointer OrientedVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::Normal,
            VertexAttribute::Format::Vector3Float
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes} );
    return format;
}

}
