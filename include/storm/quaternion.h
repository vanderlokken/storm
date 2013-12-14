#pragma once

#include <storm/matrix.h>

namespace storm {

class Quaternion {
public:
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

    float getX() const noexcept;
    float getY() const noexcept;
    float getZ() const noexcept;
    float getW() const noexcept;

    void setX( float ) noexcept;
    void setY( float ) noexcept;
    void setZ( float ) noexcept;
    void setW( float ) noexcept;

    float getLength() const noexcept;

    void normalize() noexcept;
    Quaternion getNormalized() const noexcept;

    Matrix toRotationMatrix() const noexcept;

    static Quaternion fromAxisAngle( const Vector&, float ) noexcept;
    static Quaternion slerp(
        const Quaternion&, const Quaternion&, float ) noexcept;

private:
    float _x;
    float _y;
    float _z;
    float _w;
};

Quaternion operator * ( float, const Quaternion& ) noexcept;

}
