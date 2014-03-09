#pragma once

#include <cmath>

namespace storm {

inline Vector::Vector()
    : x( 0 ), y( 0 ), z( 0 )
{
}

inline Vector::Vector( float x, float y, float z )
    : x( x ), y( y ), z( z )
{
}

inline Vector& Vector::operator += ( const Vector &vector ) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

inline Vector& Vector::operator -= ( const Vector &vector ) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

inline Vector& Vector::operator *= ( float multiplier ) {
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

inline Vector& Vector::operator /= ( float divisor ) {
    const float multiplier = 1 / divisor;
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

inline Vector Vector::operator + ( const Vector &vector ) const {
    return Vector(
        x + vector.x,
        y + vector.y,
        z + vector.z );
}

inline Vector Vector::operator - ( const Vector &vector ) const {
    return Vector(
        x - vector.x,
        y - vector.y,
        z - vector.z );
}

inline Vector Vector::operator * ( float multiplier ) const {
    return Vector(
        x * multiplier,
        y * multiplier,
        z * multiplier );
}

inline Vector Vector::operator / ( float divisor ) const {
    const float multiplier = 1 / divisor;
    return Vector(
        x * multiplier,
        y * multiplier,
        z * multiplier );
}

inline Vector Vector::operator - () const {
    return Vector( -x, -y, -z );
}

inline float Vector::getLength() const {
    return std::sqrt( x * x + y * y + z * z );
}

inline void Vector::normalize() {
    *this /= getLength();
    return;
}

inline Vector Vector::getNormalized() const {
    Vector result = *this;
    result.normalize();
    return result;
}

inline float Vector::getDotProduct(
    const Vector &first, const Vector &second )
{
    return
        first.x * second.x +
        first.y * second.y +
        first.z * second.z;
}

inline Vector Vector::getCrossProduct(
    const Vector &first, const Vector &second )
{
    return Vector(
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x );
}

inline Vector operator * ( float multiplier, const Vector &vector ) {
    return vector * multiplier;
}

}
