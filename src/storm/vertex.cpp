#include <storm/vertex.h>

#include <storm/throw_exception.h>

namespace storm {

unsigned short Vertex::Attribute::getSize() const {
    switch( format ) {
    case Format::Float:
    case Format::Vector4Uint8:
    case Format::Vector4Uint8Normalized:
    case Format::Vector2Int16:
    case Format::Vector2Int16Normalized:
    case Format::Vector2Uint16Normalized:
        return 4;
    case Format::Vector2Float:
    case Format::Vector4Int16:
    case Format::Vector4Int16Normalized:
    case Format::Vector4Uint16Normalized:
        return 8;
    case Format::Vector3Float:
        return 12;
    case Format::Vector4Float:
        return 16;
    default:
        throwRuntimeError( "'format' is invalid" );
    }
}

}
