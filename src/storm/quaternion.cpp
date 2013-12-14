#include <storm/quaternion.h>

#include <cmath>

namespace storm {

Quaternion::Quaternion() noexcept
    : _x( 0 ), _y( 0 ), _z( 0 ), _w( 0 )
{
}

Quaternion::Quaternion( float x, float y, float z, float w ) noexcept
    : _x( x ), _y( y ), _z( z ), _w( w )
{
}

Quaternion& Quaternion::operator += ( const Quaternion &other ) noexcept {
    _x += other._x;
    _y += other._y;
    _z += other._z;
    _w += other._w;
    return *this;
}

Quaternion& Quaternion::operator -= ( const Quaternion &other ) noexcept {
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    _w -= other._w;
    return *this;
}

Quaternion& Quaternion::operator *= ( const Quaternion &other ) noexcept {
    *this = *this * other;
    return *this;
}

Quaternion& Quaternion::operator *= ( float multiplier ) noexcept {
    _x *= multiplier;
    _y *= multiplier;
    _z *= multiplier;
    _w *= multiplier;
    return *this;
}

Quaternion& Quaternion::operator /= ( float divisor ) noexcept {
    _x /= divisor;
    _y /= divisor;
    _z /= divisor;
    _w /= divisor;
    return *this;
}

Quaternion Quaternion::operator + ( const Quaternion &other ) const noexcept {
    return Quaternion(
        _x + other._x, _y + other._y, _z + other._z, _w + other._w );
}

Quaternion Quaternion::operator - ( const Quaternion &other ) const noexcept {
    return Quaternion(
        _x - other._x, _y - other._y, _z - other._z, _w - other._w );
}

Quaternion Quaternion::operator * ( const Quaternion &other ) const noexcept {
    const Vector first( _x, _y, _z );
    const Vector second( other._x, other._y, other._z );

    const Vector result = Vector::getCrossProduct( first, second ) +
        second * _w + first * other._w;

    return Quaternion(
        result.getX(),
        result.getY(),
        result.getZ(),
        _w * other._w - Vector::getDotProduct(first, second) );
}

Quaternion Quaternion::operator * ( float multiplier ) const noexcept {
    return Quaternion(
        _x * multiplier, _y * multiplier, _z * multiplier, _w * multiplier );
}

Quaternion Quaternion::operator / ( float divisor ) const noexcept {
    return Quaternion(
        _x / divisor, _y / divisor, _z / divisor, _w / divisor );
}

float Quaternion::getX() const noexcept { return _x; }
float Quaternion::getY() const noexcept { return _y; }
float Quaternion::getZ() const noexcept { return _z; }
float Quaternion::getW() const noexcept { return _w; }

void Quaternion::setX( float x ) noexcept { _x = x; }
void Quaternion::setY( float y ) noexcept { _y = y; }
void Quaternion::setZ( float z ) noexcept { _z = z; }
void Quaternion::setW( float w ) noexcept { _w = w; }

float Quaternion::getLength() const noexcept {
    return sqrt( _x * _x + _y * _y + _z * _z + _w * _w );
}

void Quaternion::normalize() noexcept {
    *this /= getLength();
}

Quaternion Quaternion::getNormalized() const noexcept {
    Quaternion result( *this );
    result.normalize();
    return result;
}

Matrix Quaternion::toRotationMatrix() const noexcept {
    const float squaredLength = _x * _x + _y * _y + _z * _z + _w * _w;
    const float scale = squaredLength ? 2 / squaredLength : 0;

    const float x = _x * scale;
    const float y = _y * scale;
    const float z = _z * scale;

    const float wx = _w * x;
    const float wy = _w * y;
    const float wz = _w * z;

    const float xx = _x * x;
    const float xy = _x * y;
    const float xz = _x * z;

    const float yy = _y * y;
    const float yz = _y * z;

    const float zz = _z * z;

    return storm::Matrix(
        1 - (yy + zz), xy + wz, xz - wy, 0,
        xy - wz, 1 - (xx + zz), yz + wx, 0,
        xz + wy, yz - wx, 1 - (xx + yy), 0,
        0, 0, 0, 1
    );
}

Quaternion Quaternion::fromAxisAngle(
    const Vector &axis, float angle ) noexcept
{
    const float sine = sin( angle / 2 );
    return Quaternion(
        axis.getX() * sine,
        axis.getY() * sine,
        axis.getZ() * sine,
        cos(angle / 2) );
}

Quaternion Quaternion::slerp(
    const Quaternion &first, const Quaternion &second, float position ) noexcept
{
    if( position <= 0 )
        return first;
    if( position >= 1 )
        return second;

    const float cosine =
        first._x * second._x +
        first._y * second._y +
        first._z * second._z +
        first._w * second._w;

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

Quaternion operator * (
    float multiplier, const Quaternion &quaternion ) noexcept
{
    return quaternion * multiplier;
}

}
