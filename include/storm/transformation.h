#pragma once

#include <storm/matrix.h>

namespace storm {

Matrix createTranslationTransformation( float x, float y, float z ) noexcept;
Matrix createTranslationTransformation( const Vector &vector ) noexcept;

Matrix createScalingTransformation( float x, float y, float z ) noexcept;
Matrix createScalingTransformation( const Vector &vector ) noexcept;

Matrix createXRotationTransformation( float angle ) noexcept;
Matrix createYRotationTransformation( float angle ) noexcept;
Matrix createZRotationTransformation( float angle ) noexcept;

}
