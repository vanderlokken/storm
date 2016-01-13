#pragma once

#include <cmath>

namespace storm {

inline FlatVector::FlatVector()
    : x( 0 ), y( 0 )
{
}

inline FlatVector::FlatVector( float x, float y )
    : x( x ), y( y )
{
}

inline FlatVector& FlatVector::operator += ( const FlatVector &vector ) {
    x += vector.x;
    y += vector.y;
    return *this;
}

inline FlatVector& FlatVector::operator -= ( const FlatVector &vector ) {
    x -= vector.x;
    y -= vector.y;
    return *this;
}

inline FlatVector& FlatVector::operator *= ( const FlatVector &vector ) {
    x *= vector.x;
    y *= vector.y;
    return *this;
}

inline FlatVector& FlatVector::operator *= ( float multiplier ) {
    x *= multiplier;
    y *= multiplier;
    return *this;
}

inline FlatVector& FlatVector::operator /= ( float divisor ) {
    const float multiplier = 1 / divisor;
    x *= multiplier;
    y *= multiplier;
    return *this;
}

inline FlatVector FlatVector::operator + ( const FlatVector &vector ) const {
    return FlatVector(
        x + vector.x,
        y + vector.y );
}

inline FlatVector FlatVector::operator - ( const FlatVector &vector ) const {
    return FlatVector(
        x - vector.x,
        y - vector.y );
}

inline FlatVector FlatVector::operator * ( const FlatVector &vector ) const {
    return FlatVector(
        x * vector.x,
        y * vector.y );
}

inline FlatVector FlatVector::operator * ( float multiplier ) const {
    return FlatVector(
        x * multiplier,
        y * multiplier );
}

inline FlatVector FlatVector::operator / ( float divisor ) const {
    const float multiplier = 1 / divisor;
    return FlatVector(
        x * multiplier,
        y * multiplier );
}

inline float FlatVector::getLength() const {
    return std::sqrt( x * x + y * y );
}

inline void FlatVector::normalize() {
    *this /= getLength();
    return;
}

inline FlatVector FlatVector::getNormalized() const {
    FlatVector result = *this;
    result.normalize();
    return result;
}

inline float FlatVector::getDotProduct(
    const FlatVector &first, const FlatVector &second )
{
    return
        first.x * second.x +
        first.y * second.y;
}

}
