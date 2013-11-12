#pragma once

#include "Vector.h"
#include "Color.h"
#include "Vertex.h"

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
