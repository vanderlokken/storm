#pragma once

#include <storm/vector.h>

namespace storm {

class Matrix {
public:
    Matrix();

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
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;

    friend Vector& operator *= ( Vector&, const Matrix& );
};

Vector& operator *= ( Vector&, const Matrix& );
Vector operator * ( const Vector&, const Matrix& );

}

#include <storm/matrix.inl>
