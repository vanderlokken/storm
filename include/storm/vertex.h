#pragma once

namespace storm {

struct Vertex {

    struct Attribute {
        enum class Semantics {
            Position,
            Normal,
            Tangent,
            Binormal,
            Color,
            TextureCoordinates,
            BlendingWeights,
            BlendingIndices
        };

        enum class Format {
            Float,
            Vector2Float,
            Vector3Float,
            Vector4Float,
            Vector4Uint8,
            Vector4Uint8Normalized,
            Vector2Int16,
            Vector2Int16Normalized,
            Vector4Int16,
            Vector4Int16Normalized,
            Vector2Uint16Normalized,
            Vector4Uint16Normalized
        };

        unsigned short getSize() const;

        Semantics semantics;
        Format format;
    };

};

}
