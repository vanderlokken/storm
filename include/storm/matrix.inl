#pragma once

#include <cmath>

namespace storm {

inline Matrix::Matrix() noexcept
    : _11( 0 ), _12( 0 ), _13( 0 ), _14( 0 ),
      _21( 0 ), _22( 0 ), _23( 0 ), _24( 0 ),
      _31( 0 ), _32( 0 ), _33( 0 ), _34( 0 ),
      _41( 0 ), _42( 0 ), _43( 0 ), _44( 0 )
{
}

inline Matrix::Matrix(
    float element11, float element12, float element13, float element14,
    float element21, float element22, float element23, float element24,
    float element31, float element32, float element33, float element34,
    float element41, float element42, float element43, float element44 ) noexcept
    : _11( element11 ), _12( element12 ), _13( element13 ), _14( element14 ),
      _21( element21 ), _22( element22 ), _23( element23 ), _24( element24 ),
      _31( element31 ), _32( element32 ), _33( element33 ), _34( element34 ),
      _41( element41 ), _42( element42 ), _43( element43 ), _44( element44 )
{
}

inline float* Matrix::operator [] ( size_t index ) {
    return &_11 + index * 4;
}

inline const float* Matrix::operator [] ( size_t index ) const {
    return &_11 + index * 4;
}

inline Matrix Matrix::operator * ( const Matrix &matrix ) const noexcept {
    const float element11 =
        _11 * matrix._11 +
        _12 * matrix._21 +
        _13 * matrix._31 +
        _14 * matrix._41;

    const float element12 =
        _11 * matrix._12 +
        _12 * matrix._22 +
        _13 * matrix._32 +
        _14 * matrix._42;

    const float element13 =
        _11 * matrix._13 +
        _12 * matrix._23 +
        _13 * matrix._33 +
        _14 * matrix._43;

    const float element14 =
        _11 * matrix._14 +
        _12 * matrix._24 +
        _13 * matrix._34 +
        _14 * matrix._44;

    const float element21 =
        _21 * matrix._11 +
        _22 * matrix._21 +
        _23 * matrix._31 +
        _24 * matrix._41;

    const float element22 =
        _21 * matrix._12 +
        _22 * matrix._22 +
        _23 * matrix._32 +
        _24 * matrix._42;

    const float element23 =
        _21 * matrix._13 +
        _22 * matrix._23 +
        _23 * matrix._33 +
        _24 * matrix._43;

    const float element24 =
        _21 * matrix._14 +
        _22 * matrix._24 +
        _23 * matrix._34 +
        _24 * matrix._44;

    const float element31 =
        _31 * matrix._11 +
        _32 * matrix._21 +
        _33 * matrix._31 +
        _34 * matrix._41;

    const float element32 =
        _31 * matrix._12 +
        _32 * matrix._22 +
        _33 * matrix._32 +
        _34 * matrix._42;

    const float element33 =
        _31 * matrix._13 +
        _32 * matrix._23 +
        _33 * matrix._33 +
        _34 * matrix._43;

    const float element34 =
        _31 * matrix._14 +
        _32 * matrix._24 +
        _33 * matrix._34 +
        _34 * matrix._44;

    const float element41 =
        _41 * matrix._11 +
        _42 * matrix._21 +
        _43 * matrix._31 +
        _44 * matrix._41;

    const float element42 =
        _41 * matrix._12 +
        _42 * matrix._22 +
        _43 * matrix._32 +
        _44 * matrix._42;

    const float element43 =
        _41 * matrix._13 +
        _42 * matrix._23 +
        _43 * matrix._33 +
        _44 * matrix._43;

    const float element44 =
        _41 * matrix._14 +
        _42 * matrix._24 +
        _43 * matrix._34 +
        _44 * matrix._44;

    return Matrix(
        element11, element12, element13, element14,
        element21, element22, element23, element24,
        element31, element32, element33, element34,
        element41, element42, element43, element44 );
}

inline Matrix Matrix::operator + ( const Matrix &matrix ) const noexcept {
    return Matrix(
        _11 + matrix._11, _12 + matrix._12, _13 + matrix._13, _14 + matrix._14,
        _21 + matrix._21, _22 + matrix._22, _23 + matrix._23, _24 + matrix._24,
        _31 + matrix._31, _32 + matrix._32, _33 + matrix._33, _34 + matrix._34,
        _41 + matrix._41, _42 + matrix._42, _43 + matrix._43, _44 + matrix._44 );
}

inline Matrix& Matrix::operator *= ( const Matrix &matrix ) noexcept {
    *this = (*this) * matrix;
    return *this;
}

inline Matrix& Matrix::operator += ( const Matrix &matrix ) noexcept {
    _11 += matrix._11; _12 += matrix._12; _13 += matrix._13; _14 += matrix._14;
    _21 += matrix._21; _22 += matrix._22; _23 += matrix._23; _24 += matrix._24;
    _31 += matrix._31; _32 += matrix._32; _33 += matrix._33; _34 += matrix._34;
    _41 += matrix._41; _42 += matrix._42; _43 += matrix._43; _44 += matrix._44;
    return *this;
}

inline Matrix Matrix::operator * ( float multiplier ) const noexcept {
    return Matrix(
        _11 * multiplier, _12 * multiplier, _13 * multiplier, _14 * multiplier,
        _21 * multiplier, _22 * multiplier, _23 * multiplier, _24 * multiplier,
        _31 * multiplier, _32 * multiplier, _33 * multiplier, _34 * multiplier,
        _41 * multiplier, _42 * multiplier, _43 * multiplier, _44 * multiplier );
}

inline Matrix Matrix::getInverted() const noexcept {
    Matrix result( *this );
    result.invert();
    return result;
}

inline Vector& operator *= ( Vector &vector, const Matrix &matrix ) noexcept {
    const float x = vector.x;
    const float y = vector.y;
    const float z = vector.z;

    vector.x = x * matrix._11 + y * matrix._21 + z * matrix._31 + matrix._41;
    vector.y = x * matrix._12 + y * matrix._22 + z * matrix._32 + matrix._42;
    vector.z = x * matrix._13 + y * matrix._23 + z * matrix._33 + matrix._43;

    return vector /=
        x * matrix._14 + y * matrix._24 + z * matrix._34 + matrix._44;
}

inline Vector operator * (
    const Vector &vector, const Matrix &matrix ) noexcept
{
    Vector result( vector );
    result *= matrix;
    return result;
}

}
