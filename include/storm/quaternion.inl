#pragma once

#include <cmath>

namespace storm {

inline Quaternion::Quaternion()
    : x( 0 ), y( 0 ), z( 0 ), w( 1 )
{
}

inline Quaternion::Quaternion( float x, float y, float z, float w )
    : x( x ), y( y ), z( z ), w( w )
{
}

inline Quaternion& Quaternion::operator += ( const Quaternion &other ) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

inline Quaternion& Quaternion::operator -= ( const Quaternion &other ) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

inline Quaternion& Quaternion::operator *= ( const Quaternion &other ) {
    *this = *this * other;
    return *this;
}

inline Quaternion& Quaternion::operator *= ( float multiplier ) {
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    w *= multiplier;
    return *this;
}

inline Quaternion& Quaternion::operator /= ( float divisor ) {
    const float multiplier = 1 / divisor;
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    w *= multiplier;
    return *this;
}

inline Quaternion Quaternion::operator + ( const Quaternion &other ) const {
    return Quaternion(
        x + other.x, y + other.y, z + other.z, w + other.w );
}

inline Quaternion Quaternion::operator - ( const Quaternion &other ) const {
    return Quaternion(
        x - other.x, y - other.y, z - other.z, w - other.w );
}

inline Quaternion Quaternion::operator * ( const Quaternion &other ) const {
    const Vector first( x, y, z );
    const Vector second( other.x, other.y, other.z );

    const Vector result = Vector::getCrossProduct( first, second ) +
        second * w + first * other.w;

    return Quaternion(
        result.x,
        result.y,
        result.z,
        w * other.w - Vector::getDotProduct(first, second) );
}

inline Quaternion Quaternion::operator * ( float multiplier ) const {
    return Quaternion(
        x * multiplier, y * multiplier, z * multiplier, w * multiplier );
}

inline Quaternion Quaternion::operator / ( float divisor ) const {
    const float multiplier = 1 / divisor;
    return Quaternion(
        x * multiplier, y * multiplier, z * multiplier, w * multiplier );
}

inline float Quaternion::getLength() const {
    return sqrt( x * x + y * y + z * z + w * w );
}

inline void Quaternion::normalize() {
    *this /= getLength();
}

inline Quaternion Quaternion::getNormalized() const {
    Quaternion result( *this );
    result.normalize();
    return result;
}

inline Matrix Quaternion::toRotationMatrix() const {
    const float squaredLength = x * x + y * y + z * z + w * w;
    const float scale = squaredLength ? 2 / squaredLength : 0;

    const float x_ = x * scale;
    const float y_ = y * scale;
    const float z_ = z * scale;

    const float wx = w * x_;
    const float wy = w * y_;
    const float wz = w * z_;

    const float xx = x * x_;
    const float xy = x * y_;
    const float xz = x * z_;

    const float yy = y * y_;
    const float yz = y * z_;

    const float zz = z * z_;

    return storm::Matrix(
        1 - (yy + zz), xy + wz, xz - wy, 0,
        xy - wz, 1 - (xx + zz), yz + wx, 0,
        xz + wy, yz - wx, 1 - (xx + yy), 0,
        0, 0, 0, 1
    );
}

inline Quaternion Quaternion::fromAxisAngle(
    const Vector &axis, float angle )
{
    const float sine = sin( angle / 2 );
    return Quaternion(
        axis.x * sine,
        axis.y * sine,
        axis.z * sine,
        cos(angle / 2) );
}

inline Quaternion Quaternion::slerp(
    const Quaternion &first, const Quaternion &second, float position )
{
    if( position <= 0 )
        return first;
    if( position >= 1 )
        return second;

    const float cosine =
        first.x * second.x +
        first.y * second.y +
        first.z * second.z +
        first.w * second.w;

    const float absConsine = fabs( cosine );

    float firstScale, secondScale;
    if( 1 - absConsine > 1e-6f ) {
        const float angle = acos( cosine );
        const float sine = sin( angle );
        firstScale = sin( (1 - position) * angle ) / sine;
        secondScale = sin( position * angle ) / sine;
    } else {
        firstScale = 1 - position;
        secondScale = position;
    }

    if( cosine < 0 )
        return first * firstScale - second * secondScale;
    else
        return first * firstScale + second * secondScale;
}

inline Quaternion operator * (
    float multiplier, const Quaternion &quaternion )
{
    return quaternion * multiplier;
}

}
