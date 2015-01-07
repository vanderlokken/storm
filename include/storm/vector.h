#pragma once

namespace storm {

struct Vector {
    Vector();
    Vector( float x, float y, float z );

    Vector& operator += ( const Vector& );
    Vector& operator -= ( const Vector& );
    Vector& operator *= ( float );
    Vector& operator /= ( float );

    Vector operator + ( const Vector& ) const;
    Vector operator - ( const Vector& ) const;
    Vector operator * ( float ) const;
    Vector operator / ( float ) const;

    Vector operator - () const;

    float getLength() const;
    float getSquaredLength() const;

    void normalize();
    Vector getNormalized() const;

    static float getDotProduct( const Vector&, const Vector& );
    static Vector getCrossProduct( const Vector&, const Vector& );

    float x;
    float y;
    float z;
};

Vector operator * ( float, const Vector& );

}

#include <storm/vector.inl>
