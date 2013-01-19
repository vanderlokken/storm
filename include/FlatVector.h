#ifndef storm_FlatVector_h
#define storm_FlatVector_h

#include "Noexcept.h"

namespace storm {

class FlatVector {
public:
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

    float getX() const noexcept;
    float getY() const noexcept;

    void setX( float ) noexcept;
    void setY( float ) noexcept;

    float getLength() const noexcept;

    void normalize() noexcept;
    FlatVector getNormalized() const noexcept;

    static float getDotProduct( const FlatVector&, const FlatVector& ) noexcept;

private:
    float _x;
    float _y;
};

}

#endif