#include <storm/common_vertex_types.h>

namespace storm {

typedef VertexFormat::Attribute VertexAttribute;

VertexFormat::Pointer PositionedVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes, sizeof(PositionedVertex)} );
    return format;
}

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
        VertexFormat::create( {attributes, sizeof(TexturedVertex)} );
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
        VertexFormat::create( {attributes, sizeof(ColoredVertex)} );
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
        VertexFormat::create( {attributes, sizeof(OrientedVertex)} );
    return format;
}

VertexFormat::Pointer OrientedTexturedVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::Normal,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::TextureCoordinates,
            VertexAttribute::Format::Vector2Float
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes, sizeof(OrientedTexturedVertex)} );
    return format;
}

VertexFormat::Pointer SurfaceVertex::getFormat() {
    static const std::vector<VertexAttribute> attributes = {
        {
            VertexAttribute::Semantics::Position,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::Normal,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::Tangent,
            VertexAttribute::Format::Vector3Float
        },
        {
            VertexAttribute::Semantics::TextureCoordinates,
            VertexAttribute::Format::Vector2Float
        }
    };
    static const VertexFormat::Pointer format =
        VertexFormat::create( {attributes, sizeof(SurfaceVertex)} );
    return format;
}

}
