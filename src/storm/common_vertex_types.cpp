#include <storm/common_vertex_types.h>

namespace storm {

const Vertex::Attribute TexturedVertex::attributes[] = {
    {Vertex::Attribute::Semantics::Position,           Vertex::Attribute::Format::Vector3Float},
    {Vertex::Attribute::Semantics::TextureCoordinates, Vertex::Attribute::Format::Vector2Float} };

const Vertex::Attribute ColoredVertex::attributes[] = {
    {Vertex::Attribute::Semantics::Position, Vertex::Attribute::Format::Vector3Float},
    {Vertex::Attribute::Semantics::Color,    Vertex::Attribute::Format::Vector4Uint8Normalized} };

const Vertex::Attribute OrientedVertex::attributes[] = {
    {Vertex::Attribute::Semantics::Position, Vertex::Attribute::Format::Vector3Float},
    {Vertex::Attribute::Semantics::Normal,   Vertex::Attribute::Format::Vector3Float} };

}
