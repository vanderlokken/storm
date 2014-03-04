#pragma once

#include <cmath>

namespace storm {

inline FlatVector::FlatVector() noexcept
    : x( 0 ), y( 0 )
{
}

inline FlatVector::FlatVector( float x, float y ) noexcept
    : x( x ), y( y )
{
}

inline FlatVector& FlatVector::operator += ( const FlatVector &vector ) noexcept {
    x += vector.x;
    y += vector.y;
    return *this;
}

inline FlatVector& FlatVector::operator -= ( const FlatVector &vector ) noexcept {
    x -= vector.x;
    y -= vector.y;
    return *this;
}

inline FlatVector& FlatVector::operator *= ( float multiplier ) noexcept {
    x *= multiplier;
    y *= multiplier;
    return *this;
}

inline FlatVector& FlatVector::operator /= ( float divisor ) noexcept {
    const float multiplier = 1 / divisor;
    x *= multiplier;
    y *= multiplier;
    return *this;
}

inline FlatVector FlatVector::operator + ( const FlatVector &vector ) const noexcept {
    return FlatVector(
        x + vector.x,
        y + vector.y );
}

inline FlatVector FlatVector::operator - ( const FlatVector &vector ) const noexcept {
    return FlatVector(
        x - vector.x,
        y - vector.y );
}

inline FlatVector FlatVector::operator * ( float multiplier ) const noexcept {
    return FlatVector(
        x * multiplier,
        y * multiplier );
}

inline FlatVector FlatVector::operator / ( float divisor ) const noexcept {
    const float multiplier = 1 / divisor;
    return FlatVector(
        x * multiplier,
        y * multiplier );
}

inline float FlatVector::getLength() const noexcept {
    return std::sqrt( x * x + y * y );
}

inline void FlatVector::normalize() noexcept {
    *this /= getLength();
    return;
}

inline FlatVector FlatVector::getNormalized() const noexcept {
    FlatVector result = *this;
    result.normalize();
    return result;
}

inline float FlatVector::getDotProduct(
    const FlatVector &first, const FlatVector &second ) noexcept
{
    return
        first.x * second.x +
        first.y * second.y;
}

}
