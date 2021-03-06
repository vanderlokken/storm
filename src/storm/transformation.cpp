#include <storm/transformation.h>

#include <cmath>

namespace storm {

Matrix createTranslationTransformation( float x, float y, float z ) {
    return Matrix( 1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   x, y, z, 1 );
}

Matrix createTranslationTransformation( const Vector &vector ) {
    return createTranslationTransformation( vector.x, vector.y, vector.z );
}

Matrix createScalingTransformation( float x, float y, float z ) {
    return Matrix( x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1 );
}

Matrix createScalingTransformation( const Vector &vector ) {
    return createScalingTransformation( vector.x, vector.y, vector.z );
}

Matrix createXRotationTransformation( float angle ) {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( 1,      0,      0,      0,
                   0, cosine,  -sine,      0,
                   0,   sine, cosine,      0,
                   0,      0,      0,      1 );
}

Matrix createYRotationTransformation( float angle ) {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( cosine,      0,   sine,      0,
                        0,      1,      0,      0,
                    -sine,      0, cosine,      0,
                        0,      0,      0,      1 );
}

Matrix createZRotationTransformation( float angle ) {
    const float   sine = sin( angle );
    const float cosine = cos( angle );

    return Matrix( cosine,  -sine,      0,      0,
                     sine, cosine,      0,      0,
                        0,      0,      1,      0,
                        0,      0,      0,      1 );
}

}