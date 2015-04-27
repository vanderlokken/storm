#pragma once

#include <storm/matrix.h>
#include <storm/vector.h>

namespace storm {

struct Quaternion {
    Quaternion();
    Quaternion( float, float, float, float );

    Quaternion& operator += ( const Quaternion& );
    Quaternion& operator -= ( const Quaternion& );
    Quaternion& operator *= ( const Quaternion& );
    Quaternion& operator *= ( float );
    Quaternion& operator /= ( float );

    Quaternion operator + ( const Quaternion& ) const;
    Quaternion operator - ( const Quaternion& ) const;
    Quaternion operator * ( const Quaternion& ) const;
    Quaternion operator * ( float ) const;
    Quaternion operator / ( float ) const;

    float getLength() const;

    void normalize();
    Quaternion getNormalized() const;

    Quaternion getConjugate() const;

    Matrix toRotationMatrix() const;

    static Quaternion fromAxisAngle( const Vector&, float );
    static Quaternion fromAxes( const Vector&, const Vector& );
    static Quaternion slerp(
        const Quaternion&, const Quaternion&, float );

    float x;
    float y;
    float z;
    float w;
};

Quaternion operator * ( float, const Quaternion& );

}

#include <storm/quaternion.inl>
