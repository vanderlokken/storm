#pragma once

#include <storm/color.h>
#include <storm/vector.h>
#include <storm/vertex.h>

namespace storm {

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
