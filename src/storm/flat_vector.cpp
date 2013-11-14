#include <storm/flat_vector.h>

#include <cmath>

namespace storm {

FlatVector::FlatVector() noexcept
    : _x( 0 ), _y( 0 )
{
}

FlatVector::FlatVector( float x, float y ) noexcept
    : _x( x ), _y( y )
{
}

FlatVector& FlatVector::operator += ( const FlatVector &vector ) noexcept {
    _x += vector._x;
    _y += vector._y;
    return *this;
}

FlatVector& FlatVector::operator -= ( const FlatVector &vector ) noexcept {
    _x -= vector._x;
    _y -= vector._y;
    return *this;
}

FlatVector& FlatVector::operator *= ( float multiplier ) noexcept {
    _x *= multiplier;
    _y *= multiplier;
    return *this;
}

FlatVector& FlatVector::operator /= ( float divisor ) noexcept {
    _x /= divisor;
    _y /= divisor;
    return *this;
}

FlatVector FlatVector::operator + ( const FlatVector &vector ) const noexcept {
    return FlatVector(
        _x + vector._x,
        _y + vector._y );
}

FlatVector FlatVector::operator - ( const FlatVector &vector ) const noexcept {
    return FlatVector(
        _x - vector._x,
        _y - vector._y );
}

FlatVector FlatVector::operator * ( float multiplier ) const noexcept {
    return FlatVector(
        _x * multiplier,
        _y * multiplier );
}

FlatVector FlatVector::operator / ( float divisor ) const noexcept {
    return FlatVector(
        _x / divisor,
        _y / divisor );
}

float FlatVector::getX() const noexcept {
    return _x;
}

float FlatVector::getY() const noexcept {
    return _y;
}

void FlatVector::setX( float x ) noexcept {
    _x = x;
    return;
}

void FlatVector::setY( float y ) noexcept {
    _y = y;
    return;
}

float FlatVector::getLength() const noexcept {
    return std::sqrt( _x * _x + _y * _y );
}

void FlatVector::normalize() noexcept {
    *this /= getLength();
    return;
}

FlatVector FlatVector::getNormalized() const noexcept {
    FlatVector result = *this;
    result.normalize();
    return result;
}

float FlatVector::getDotProduct( const FlatVector &first, const FlatVector &second ) noexcept {
    return
        first._x * second._x +
        first._y * second._y;
}

}