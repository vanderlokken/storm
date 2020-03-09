#pragma once

#include <memory>
#include <vector>

namespace storm {

class VertexFormat {
public:
    using Pointer = std::shared_ptr<VertexFormat>;

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

        Semantics semantics;
        Format format;
    };

    struct Description {
        std::vector<Attribute> attributes;
        size_t size;
    };

    static Pointer create( const Description& );

    virtual ~VertexFormat() = default;

    virtual const Description& getDescription() const = 0;
};

}
