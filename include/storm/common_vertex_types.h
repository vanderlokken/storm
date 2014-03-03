#pragma once

#include <storm/color.h>
#include <storm/flat_vector.h>
#include <storm/vector.h>
#include <storm/vertex_format.h>

namespace storm {

struct TexturedVertex {
    Vector position;
    FlatVector textureCoordinates;

    static VertexFormat::Pointer getFormat();
};

struct ColoredVertex {
    Vector position;
    Color color;

    static VertexFormat::Pointer getFormat();
};

struct OrientedVertex {
    Vector position;
    Vector normal;

    static VertexFormat::Pointer getFormat();
};

}
