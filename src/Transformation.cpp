#include "Transformation.h"

#include <cmath>

namespace storm {

Matrix createTranslationTransformation( float x, float y, float z ) noexcept {
    return Matrix( 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   x, y, z, 1 );
}

Matrix createScalingTransformation( float x, float y, float z ) noexcept {
    return Matrix( x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1 );
}

Matrix createXRotationTransformation( float angle ) noexcept {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( 1,      0,      0,      0,
                   0, cosine,  -sine,      0,
                   0,   sine, cosine,      0,
                   0,      0,      0,      1 );
}

Matrix createYRotationTransformation( float angle ) noexcept {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( cosine,      0,   sine,      0,
                        0,      1,      0,      0,
                    -sine,      0, cosine,      0,
                        0,      0,      0,      1 );
}

Matrix createZRotationTransformation( float angle ) noexcept {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( cosine,  -sine,      0,      0,
                     sine, cosine,      0,      0,
                        0,      0,      1,      0,
                        0,      0,      0,      1 );
}

}