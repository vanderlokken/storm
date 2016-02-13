#pragma once

#include <storm/color.h>
#include <storm/vector.h>
#include <storm/vertex_format.h>

namespace storm {

struct PositionedVertex {
    Vector position;

    static VertexFormat::Pointer getFormat();
};

struct TexturedVertex {
    Vector position;
    Vector2d textureCoordinates;

    static VertexFormat::Pointer getFormat();
};

struct ColoredVertex {
    Vector position;
    CompressedColor color;

    static VertexFormat::Pointer getFormat();
};

struct OrientedVertex {
    Vector position;
    Vector normal;

    static VertexFormat::Pointer getFormat();
};

struct OrientedTexturedVertex {
    Vector position;
    Vector normal;
    Vector2d textureCoordinates;

    static VertexFormat::Pointer getFormat();
};

struct SurfaceVertex {
    Vector position;
    Vector normal;
    Vector tangent;
    Vector2d textureCoordinates;

    static VertexFormat::Pointer getFormat();
};

}
