#pragma once

#include <storm/vector.h>

namespace storm {

class Matrix {
public:
    Matrix() = default;

    Matrix(
        float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34,
        float _41, float _42, float _43, float _44 );

    float* operator [] ( unsigned int index );
    const float* operator [] ( unsigned int index ) const;

    Matrix& operator *= ( const Matrix& );
    Matrix& operator += ( const Matrix& );

    Matrix operator * ( const Matrix& ) const;
    Matrix operator + ( const Matrix& ) const;

    Matrix& operator *= ( float );

    Matrix operator * ( float ) const;

    float getDeterminant() const;

    void invert();
    Matrix getInverted() const;

    static const Matrix Identity;

private:
    float _11 = 0, _12 = 0, _13 = 0, _14 = 0;
    float _21 = 0, _22 = 0, _23 = 0, _24 = 0;
    float _31 = 0, _32 = 0, _33 = 0, _34 = 0;
    float _41 = 0, _42 = 0, _43 = 0, _44 = 0;

    friend Vector& operator *= ( Vector&, const Matrix& );
};

Vector& operator *= ( Vector&, const Matrix& );
Vector operator * ( const Vector&, const Matrix& );

}

#include <storm/matrix.inl>
