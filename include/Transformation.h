#ifndef storm_Transformation_h
#define storm_Transformation_h

#include "Matrix.h"

namespace storm {

Matrix createTranslationTransformation( float x, float y, float z ) noexcept;
Matrix createTranslationTransformation( const Vector &vector ) noexcept;

Matrix createScalingTransformation( float x, float y, float z ) noexcept;
Matrix createScalingTransformation( const Vector &vector ) noexcept;

Matrix createXRotationTransformation( float angle ) noexcept;
Matrix createYRotationTransformation( float angle ) noexcept;
Matrix createZRotationTransformation( float angle ) noexcept;

}

#endif