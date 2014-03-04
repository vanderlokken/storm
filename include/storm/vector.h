#pragma once

#include <storm/noexcept.h>

namespace storm {

struct Vector {
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

    float getLength() const noexcept;

    void normalize() noexcept;
    Vector getNormalized() const noexcept;

    static float getDotProduct( const Vector&, const Vector& ) noexcept;
    static Vector getCrossProduct( const Vector&, const Vector& ) noexcept;

    float x;
    float y;
    float z;
};

Vector operator * ( float, const Vector& ) noexcept;

}

#include <storm/vector.inl>
