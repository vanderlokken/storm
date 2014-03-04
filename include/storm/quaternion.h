#pragma once

#include <storm/matrix.h>

namespace storm {

struct Quaternion {
    Quaternion() noexcept;
    Quaternion( float, float, float, float ) noexcept;

    Quaternion& operator += ( const Quaternion& ) noexcept;
    Quaternion& operator -= ( const Quaternion& ) noexcept;
    Quaternion& operator *= ( const Quaternion& ) noexcept;
    Quaternion& operator *= ( float ) noexcept;
    Quaternion& operator /= ( float ) noexcept;

    Quaternion operator + ( const Quaternion& ) const noexcept;
    Quaternion operator - ( const Quaternion& ) const noexcept;
    Quaternion operator * ( const Quaternion& ) const noexcept;
    Quaternion operator * ( float ) const noexcept;
    Quaternion operator / ( float ) const noexcept;

    float getLength() const noexcept;

    void normalize() noexcept;
    Quaternion getNormalized() const noexcept;

    Matrix toRotationMatrix() const noexcept;

    static Quaternion fromAxisAngle( const Vector&, float ) noexcept;
    static Quaternion slerp(
        const Quaternion&, const Quaternion&, float ) noexcept;

    float x;
    float y;
    float z;
    float w;
};

Quaternion operator * ( float, const Quaternion& ) noexcept;

}

#include <storm/quaternion.inl>
