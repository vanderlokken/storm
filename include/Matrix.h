#ifndef storm_Matrix_h
#define storm_Matrix_h

#include <cstddef>

#include "Noexcept.h"
#include "Vector.h"

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
    
    Matrix& operator *= ( const Matrix& ) const noexcept;
    Matrix& operator += ( const Matrix& ) const noexcept;
    
    Matrix operator * ( const Matrix& ) const noexcept;
    Matrix operator + ( const Matrix& ) const noexcept;
    
    Matrix operator * ( float ) const noexcept;
    
    static const Matrix Identity;
    
private:
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};

Vector& operator *= ( Vector &vector, const Matrix &matrix ) noexcept;
Vector operator * ( const Vector &vector, const Matrix &matrix ) noexcept;

}

#endif
