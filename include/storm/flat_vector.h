#pragma once

namespace storm {

struct FlatVector {
    FlatVector();
    FlatVector( float x, float y );

    FlatVector& operator += ( const FlatVector& );
    FlatVector& operator -= ( const FlatVector& );
    FlatVector& operator *= ( const FlatVector& );
    FlatVector& operator *= ( float );
    FlatVector& operator /= ( float );

    FlatVector operator + ( const FlatVector& ) const;
    FlatVector operator - ( const FlatVector& ) const;
    FlatVector operator * ( const FlatVector& ) const;
    FlatVector operator * ( float ) const;
    FlatVector operator / ( float ) const;

    float getLength() const;

    void normalize();
    FlatVector getNormalized() const;

    static float getDotProduct( const FlatVector&, const FlatVector& );

    float x;
    float y;
};

}

#include <storm/flat_vector.inl>
