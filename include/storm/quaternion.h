#pragma once

#include <storm/matrix.h>

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

    Matrix toRotationMatrix() const;

    static Quaternion fromAxisAngle( const Vector&, float );
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
