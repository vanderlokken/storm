#pragma once

#include <cmath>

namespace storm {

inline Vector::Vector() noexcept
    : x( 0 ), y( 0 ), z( 0 )
{
}

inline Vector::Vector( float x, float y, float z ) noexcept
    : x( x ), y( y ), z( z )
{
}

inline Vector& Vector::operator += ( const Vector &vector ) noexcept {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

inline Vector& Vector::operator -= ( const Vector &vector ) noexcept {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

inline Vector& Vector::operator *= ( float multiplier ) noexcept {
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

inline Vector& Vector::operator /= ( float divisor ) noexcept {
    const float multiplier = 1 / divisor;
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

inline Vector Vector::operator + ( const Vector &vector ) const noexcept {
    return Vector(
        x + vector.x,
        y + vector.y,
        z + vector.z );
}

inline Vector Vector::operator - ( const Vector &vector ) const noexcept {
    return Vector(
        x - vector.x,
        y - vector.y,
        z - vector.z );
}

inline Vector Vector::operator * ( float multiplier ) const noexcept {
    return Vector(
        x * multiplier,
        y * multiplier,
        z * multiplier );
}

inline Vector Vector::operator / ( float divisor ) const noexcept {
    const float multiplier = 1 / divisor;
    return Vector(
        x * multiplier,
        y * multiplier,
        z * multiplier );
}

inline Vector Vector::operator - () const noexcept {
    return Vector( -x, -y, -z );
}

inline float Vector::getLength() const noexcept {
    return std::sqrt( x * x + y * y + z * z );
}

inline void Vector::normalize() noexcept {
    *this /= getLength();
    return;
}

inline Vector Vector::getNormalized() const noexcept {
    Vector result = *this;
    result.normalize();
    return result;
}

inline float Vector::getDotProduct(
    const Vector &first, const Vector &second ) noexcept
{
    return
        first.x * second.x +
        first.y * second.y +
        first.z * second.z;
}

inline Vector Vector::getCrossProduct(
    const Vector &first, const Vector &second ) noexcept
{
    return Vector(
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x );
}

inline Vector operator * ( float multiplier, const Vector &vector ) noexcept {
    return vector * multiplier;
}

}
