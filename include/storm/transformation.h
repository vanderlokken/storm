#pragma once

#include <storm/matrix.h>

namespace storm {

Matrix createTranslationTransformation( float x, float y, float z );
Matrix createTranslationTransformation( const Vector &vector );

Matrix createScalingTransformation( float x, float y, float z );
Matrix createScalingTransformation( const Vector &vector );

Matrix createXRotationTransformation( float angle );
Matrix createYRotationTransformation( float angle );
Matrix createZRotationTransformation( float angle );

}
