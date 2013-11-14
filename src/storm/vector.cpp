#include <storm/vector.h>

#include <cmath>

namespace storm {

Vector::Vector() noexcept
    : _x( 0 ), _y( 0 ), _z( 0 )
{
}

Vector::Vector( float x, float y, float z ) noexcept
    : _x( x ), _y( y ), _z( z )
{
}

Vector& Vector::operator += ( const Vector &vector ) noexcept {
    _x += vector._x;
    _y += vector._y;
    _z += vector._z;
    return *this;
}

Vector& Vector::operator -= ( const Vector &vector ) noexcept {
    _x -= vector._x;
    _y -= vector._y;
    _z -= vector._z;
    return *this;
}

Vector& Vector::operator *= ( float multiplier ) noexcept {
    _x *= multiplier;
    _y *= multiplier;
    _z *= multiplier;
    return *this;
}

Vector& Vector::operator /= ( float divisor ) noexcept {
    _x /= divisor;
    _y /= divisor;
    _z /= divisor;
    return *this;
}

Vector Vector::operator + ( const Vector &vector ) const noexcept {
    return Vector(
        _x + vector._x,
        _y + vector._y,
        _z + vector._z );
}

Vector Vector::operator - ( const Vector &vector ) const noexcept {
    return Vector(
        _x - vector._x,
        _y - vector._y,
        _z - vector._z );
}

Vector Vector::operator * ( float multiplier ) const noexcept {
    return Vector(
        _x * multiplier,
        _y * multiplier,
        _z * multiplier );
}

Vector Vector::operator / ( float divisor ) const noexcept {
    return Vector(
        _x / divisor,
        _y / divisor,
        _z / divisor );
}

Vector Vector::operator - () const noexcept {
    return Vector( -_x, -_y, -_z );
}

float Vector::getX() const noexcept {
    return _x;
}

float Vector::getY() const noexcept {
    return _y;
}

float Vector::getZ() const noexcept {
    return _z;
}

void Vector::setX( float x ) noexcept {
    _x = x;
    return;
}

void Vector::setY( float y ) noexcept {
    _y = y;
    return;
}

void Vector::setZ( float z ) noexcept {
    _z = z;
    return;
}

float Vector::getLength() const noexcept {
    return std::sqrt( _x * _x + _y * _y + _z * _z );
}

void Vector::normalize() noexcept {
    *this /= getLength();
    return;
}

Vector Vector::getNormalized() const noexcept {
    Vector result = *this;
    result.normalize();
    return result;
}

float Vector::getDotProduct( const Vector &first, const Vector &second ) noexcept {
    return
        first._x * second._x +
        first._y * second._y +
        first._z * second._z;
}

Vector Vector::getCrossProduct( const Vector &first, const Vector &second ) noexcept {
    return Vector(
        first._y * second._z - first._z * second._y,
        first._z * second._x - first._x * second._z,
        first._x * second._y - first._y * second._x );
}

Vector operator * ( float multiplier, const Vector &vector ) noexcept {
    return vector * multiplier;
}

}