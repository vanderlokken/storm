#pragma once

#include <storm/noexcept.h>

namespace storm {

struct FlatVector {
    FlatVector() noexcept;
    FlatVector( float x, float y ) noexcept;

    FlatVector& operator += ( const FlatVector& ) noexcept;
    FlatVector& operator -= ( const FlatVector& ) noexcept;
    FlatVector& operator *= ( float ) noexcept;
    FlatVector& operator /= ( float ) noexcept;

    FlatVector operator + ( const FlatVector& ) const noexcept;
    FlatVector operator - ( const FlatVector& ) const noexcept;
    FlatVector operator * ( float ) const noexcept;
    FlatVector operator / ( float ) const noexcept;

    float getLength() const noexcept;

    void normalize() noexcept;
    FlatVector getNormalized() const noexcept;

    static float getDotProduct( const FlatVector&, const FlatVector& ) noexcept;

    float x;
    float y;
};

}

#include <storm/flat_vector.inl>
