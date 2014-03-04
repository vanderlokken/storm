#include <storm/matrix.h>

#include <cmath>

namespace storm {

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

const Matrix Matrix::Identity(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 );

}
