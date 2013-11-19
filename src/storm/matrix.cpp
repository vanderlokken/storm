#include <storm/matrix.h>

#include <cmath>

namespace storm {

Matrix::Matrix() noexcept
    : _11( 0 ), _12( 0 ), _13( 0 ), _14( 0 ),
      _21( 0 ), _22( 0 ), _23( 0 ), _24( 0 ),
      _31( 0 ), _32( 0 ), _33( 0 ), _34( 0 ),
      _41( 0 ), _42( 0 ), _43( 0 ), _44( 0 )
{
}

Matrix::Matrix(
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

float* Matrix::operator [] ( size_t index ) {
    return &_11 + index * 4;
}

const float* Matrix::operator [] ( size_t index ) const {
    return &_11 + index * 4;
}

Matrix Matrix::operator * ( const Matrix &matrix ) const noexcept {
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

Matrix Matrix::operator + ( const Matrix &matrix ) const noexcept {
    return Matrix(
        _11 + matrix._11, _12 + matrix._12, _13 + matrix._13, _14 + matrix._14,
        _21 + matrix._21, _22 + matrix._22, _23 + matrix._23, _24 + matrix._24,
        _31 + matrix._31, _32 + matrix._32, _33 + matrix._33, _34 + matrix._34,
        _41 + matrix._41, _42 + matrix._42, _43 + matrix._43, _44 + matrix._44 );
}

Matrix& Matrix::operator *= ( const Matrix &matrix ) noexcept {
    *this = (*this) * matrix;
    return *this;
}

Matrix& Matrix::operator += ( const Matrix &matrix ) noexcept {
    _11 += matrix._11; _12 += matrix._12; _13 += matrix._13; _14 += matrix._14;
    _21 += matrix._21; _22 += matrix._22; _23 += matrix._23; _24 += matrix._24;
    _31 += matrix._31; _32 += matrix._32; _33 += matrix._33; _34 += matrix._34;
    _41 += matrix._41; _42 += matrix._42; _43 += matrix._43; _44 += matrix._44;
    return *this;
}

Matrix Matrix::operator * ( float multiplier ) const noexcept {
    return Matrix(
        _11 * multiplier, _12 * multiplier, _13 * multiplier, _14 * multiplier,
        _21 * multiplier, _22 * multiplier, _23 * multiplier, _24 * multiplier,
        _31 * multiplier, _32 * multiplier, _33 * multiplier, _34 * multiplier,
        _41 * multiplier, _42 * multiplier, _43 * multiplier, _44 * multiplier );
}

float Matrix::getDeterminant() const noexcept {
    const float _2x2Determinant1 = _33 * _44 - _34 * _43;
    const float _2x2Determinant2 = _32 * _44 - _34 * _42;
    const float _2x2Determinant3 = _32 * _43 - _33 * _42;
    const float _2x2Determinant4 = _31 * _44 - _34 * _41;
    const float _2x2Determinant5 = _31 * _43 - _33 * _41;
    const float _2x2Determinant6 = _31 * _42 - _32 * _41;

    const float _3x3Determinant1 = _22 * _2x2Determinant1 - _23 * _2x2Determinant2 + _24 * _2x2Determinant3;
    const float _3x3Determinant2 = _21 * _2x2Determinant1 - _23 * _2x2Determinant4 + _24 * _2x2Determinant5;
    const float _3x3Determinant3 = _21 * _2x2Determinant2 - _22 * _2x2Determinant4 + _24 * _2x2Determinant6;
    const float _3x3Determinant4 = _21 * _2x2Determinant3 - _22 * _2x2Determinant5 + _23 * _2x2Determinant6;

    return _11 * _3x3Determinant1 - _12 * _3x3Determinant2 + _13 * _3x3Determinant3 - _14 * _3x3Determinant4;
}

void Matrix::invert() noexcept {
    const float _2x2Determinant1 = _33 * _44 - _34 * _43;
    const float _2x2Determinant2 = _32 * _44 - _34 * _42;
    const float _2x2Determinant3 = _32 * _43 - _33 * _42;
    const float _2x2Determinant4 = _31 * _44 - _34 * _41;
    const float _2x2Determinant5 = _31 * _43 - _33 * _41;
    const float _2x2Determinant6 = _31 * _42 - _32 * _41;

    const float _3x3Determinant1 = _22 * _2x2Determinant1 - _23 * _2x2Determinant2 + _24 * _2x2Determinant3;
    const float _3x3Determinant2 = _21 * _2x2Determinant1 - _23 * _2x2Determinant4 + _24 * _2x2Determinant5;
    const float _3x3Determinant3 = _21 * _2x2Determinant2 - _22 * _2x2Determinant4 + _24 * _2x2Determinant6;
    const float _3x3Determinant4 = _21 * _2x2Determinant3 - _22 * _2x2Determinant5 + _23 * _2x2Determinant6;

    const float _4x4Determinant = _11 * _3x3Determinant1 - _12 * _3x3Determinant2 + _13 * _3x3Determinant3 - _14 * _3x3Determinant4;

    if( abs(_4x4Determinant) < 1e-14 )
        return;

    const float _3x3Determinant5 = _12 * _2x2Determinant1 - _13 * _2x2Determinant2 + _14 * _2x2Determinant3;
    const float _3x3Determinant6 = _11 * _2x2Determinant1 - _13 * _2x2Determinant4 + _14 * _2x2Determinant5;
    const float _3x3Determinant7 = _11 * _2x2Determinant2 - _12 * _2x2Determinant4 + _14 * _2x2Determinant6;
    const float _3x3Determinant8 = _11 * _2x2Determinant3 - _12 * _2x2Determinant5 + _13 * _2x2Determinant6;

    const float _2x2Determinant7  = _23 * _44 - _24 * _43;
    const float _2x2Determinant8  = _22 * _44 - _24 * _42;
    const float _2x2Determinant9  = _22 * _43 - _23 * _42;
    const float _2x2Determinant10 = _21 * _44 - _24 * _41;
    const float _2x2Determinant11 = _21 * _43 - _23 * _41;
    const float _2x2Determinant12 = _21 * _42 - _22 * _41;

    const float _3x3Determinant9  = _12 * _2x2Determinant7 - _13 * _2x2Determinant8  + _14 * _2x2Determinant9;
    const float _3x3Determinant10 = _11 * _2x2Determinant7 - _13 * _2x2Determinant10 + _14 * _2x2Determinant11;
    const float _3x3Determinant11 = _11 * _2x2Determinant8 - _12 * _2x2Determinant10 + _14 * _2x2Determinant12;
    const float _3x3Determinant12 = _11 * _2x2Determinant9 - _12 * _2x2Determinant11 + _13 * _2x2Determinant12;

    const float _2x2Determinant13 = _23 * _34 - _24 * _33;
    const float _2x2Determinant14 = _22 * _34 - _24 * _32;
    const float _2x2Determinant15 = _22 * _33 - _23 * _32;
    const float _2x2Determinant16 = _21 * _34 - _24 * _31;
    const float _2x2Determinant17 = _21 * _33 - _23 * _31;
    const float _2x2Determinant18 = _21 * _32 - _22 * _31;

    const float _3x3Determinant13 = _12 * _2x2Determinant13 - _13 * _2x2Determinant14 + _14 * _2x2Determinant15;
    const float _3x3Determinant14 = _11 * _2x2Determinant13 - _13 * _2x2Determinant16 + _14 * _2x2Determinant17;
    const float _3x3Determinant15 = _11 * _2x2Determinant14 - _12 * _2x2Determinant16 + _14 * _2x2Determinant18;
    const float _3x3Determinant16 = _11 * _2x2Determinant15 - _12 * _2x2Determinant17 + _13 * _2x2Determinant18;

    const float invertedDeterminant = 1 / _4x4Determinant;

    _11 =  _3x3Determinant1  * invertedDeterminant;
    _21 = -_3x3Determinant2  * invertedDeterminant;
    _31 =  _3x3Determinant3  * invertedDeterminant;
    _41 = -_3x3Determinant4  * invertedDeterminant;
    _12 = -_3x3Determinant5  * invertedDeterminant;
    _22 =  _3x3Determinant6  * invertedDeterminant;
    _32 = -_3x3Determinant7  * invertedDeterminant;
    _42 =  _3x3Determinant8  * invertedDeterminant;
    _13 =  _3x3Determinant9  * invertedDeterminant;
    _23 = -_3x3Determinant10 * invertedDeterminant;
    _33 =  _3x3Determinant11 * invertedDeterminant;
    _43 = -_3x3Determinant12 * invertedDeterminant;
    _14 = -_3x3Determinant13 * invertedDeterminant;
    _24 =  _3x3Determinant14 * invertedDeterminant;
    _34 = -_3x3Determinant15 * invertedDeterminant;
    _44 =  _3x3Determinant16 * invertedDeterminant;
}

Matrix Matrix::getInverted() const noexcept {
    Matrix result( *this );
    result.invert();
    return result;
}

const Matrix Matrix::Identity(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 );

Vector& operator *= ( Vector &vector, const Matrix &matrix ) noexcept {
    const float x = vector.getX();
    const float y = vector.getY();
    const float z = vector.getZ();

    float newX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + matrix[3][0];
    float newY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + matrix[3][1];
    float newZ = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + matrix[3][2];

    const float newW = x * matrix[0][3] + y * matrix[1][3] + z * matrix[2][3] + matrix[3][3];

    if( newW != 1 ) {
        newX /= newW;
        newY /= newW;
        newZ /= newW;
    }

    vector.setX( newX );
    vector.setY( newY );
    vector.setZ( newZ );

    return vector;
}

Vector operator * ( const Vector &vector, const Matrix &matrix ) noexcept {
    Vector result( vector );
    result *= matrix;
    return result;
}

}