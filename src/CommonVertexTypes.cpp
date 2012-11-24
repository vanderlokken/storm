#include "CommonVertexTypes.h"

namespace storm {

const Vertex::Attribute ColoredVertex::attributes[] = {
    {Vertex::Attribute::SemanticsPosition, Vertex::Attribute::Format3Float},
    {Vertex::Attribute::SemanticsColor,    Vertex::Attribute::Format4Uint8Normalized} };

const Vertex::Attribute OrientedVertex::attributes[] = {
    {Vertex::Attribute::SemanticsPosition, Vertex::Attribute::Format3Float},
    {Vertex::Attribute::SemanticsNormal,   Vertex::Attribute::Format3Float} };

}
