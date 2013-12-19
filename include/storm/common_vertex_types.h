#pragma once

#include <storm/color.h>
#include <storm/flat_vector.h>
#include <storm/vector.h>
#include <storm/vertex.h>

namespace storm {

struct TexturedVertex {
    Vector position;
    FlatVector textureCoordinates;

    static const Vertex::Attribute attributes[2];
};

struct ColoredVertex {
    Vector position;
    Color color;

    static const Vertex::Attribute attributes[2];
};

struct OrientedVertex {
    Vector position;
    Vector normal;

    static const Vertex::Attribute attributes[2];
};

}
