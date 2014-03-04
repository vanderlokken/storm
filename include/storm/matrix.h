#pragma once

#include <cstddef>

#include <storm/noexcept.h>
#include <storm/vector.h>

namespace storm {

class Matrix {
public:
    Matrix() noexcept;

    Matrix(
        float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34,
        float _41, float _42, float _43, float _44 ) noexcept;

    float* operator [] ( size_t index );
    const float* operator [] ( size_t index ) const;

    Matrix& operator *= ( const Matrix& ) noexcept;
    Matrix& operator += ( const Matrix& ) noexcept;

    Matrix operator * ( const Matrix& ) const noexcept;
    Matrix operator + ( const Matrix& ) const noexcept;

    Matrix operator * ( float ) const noexcept;

    float getDeterminant() const noexcept;

    void invert() noexcept;
    Matrix getInverted() const noexcept;

    static const Matrix Identity;

private:
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;

    friend Vector& operator *= ( Vector&, const Matrix& ) noexcept;
};

Vector& operator *= ( Vector&, const Matrix& ) noexcept;
Vector operator * ( const Vector&, const Matrix& ) noexcept;

}

#include <storm/matrix.inl>
