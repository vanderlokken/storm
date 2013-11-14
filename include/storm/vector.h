#pragma once

#include <storm/noexcept.h>

namespace storm {

class Vector {
public:
    Vector() noexcept;
    Vector( float x, float y, float z ) noexcept;

    Vector& operator += ( const Vector& ) noexcept;
    Vector& operator -= ( const Vector& ) noexcept;
    Vector& operator *= ( float ) noexcept;
    Vector& operator /= ( float ) noexcept;

    Vector operator + ( const Vector& ) const noexcept;
    Vector operator - ( const Vector& ) const noexcept;
    Vector operator * ( float ) const noexcept;
    Vector operator / ( float ) const noexcept;

    Vector operator - () const noexcept;

    float getX() const noexcept;
    float getY() const noexcept;
    float getZ() const noexcept;

    void setX( float ) noexcept;
    void setY( float ) noexcept;
    void setZ( float ) noexcept;

    float getLength() const noexcept;

    void normalize() noexcept;
    Vector getNormalized() const noexcept;

    static float getDotProduct( const Vector&, const Vector& ) noexcept;
    static Vector getCrossProduct( const Vector&, const Vector& ) noexcept;

private:
    float _x;
    float _y;
    float _z;
};

Vector operator * ( float, const Vector& ) noexcept;

}
