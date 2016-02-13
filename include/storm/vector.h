#pragma once

namespace storm {

template<class Type, size_t Size>
struct VectorData {
    Type elements[Size];
};

// Disable MSVC warning "nonstandard extension used: nameless struct/union"
#pragma warning( push )
#pragma warning( disable : 4201 )

template<class Type>
struct VectorData<Type, 1> {
    union { Type elements[1]; struct {Type x;}; };
};

template<class Type>
struct VectorData<Type, 2> {
    union { Type elements[2]; struct {Type x; Type y;}; };
};

template<class Type>
struct VectorData<Type, 3> {
    union { Type elements[3]; struct {Type x; Type y; Type z;}; };
};

template<class Type>
struct VectorData<Type, 4> {
    union { Type elements[4]; struct {Type x; Type y; Type z; Type w;}; };
};

#pragma warning( pop )

template<class Type, size_t Size>
struct BasicVector : VectorData<Type, Size> {
    BasicVector();

    template<class... Values>
    BasicVector( Values... values );

    BasicVector<Type, Size>& operator += ( const BasicVector<Type, Size>& );
    BasicVector<Type, Size>& operator -= ( const BasicVector<Type, Size>& );
    BasicVector<Type, Size>& operator *= ( const BasicVector<Type, Size>& );
    BasicVector<Type, Size>& operator /= ( const BasicVector<Type, Size>& );

    BasicVector<Type, Size>& operator += ( const Type& );
    BasicVector<Type, Size>& operator -= ( const Type& );
    BasicVector<Type, Size>& operator *= ( const Type& );
    BasicVector<Type, Size>& operator /= ( const Type& );

    BasicVector<Type, Size> operator + ( const BasicVector<Type, Size>& ) const;
    BasicVector<Type, Size> operator - ( const BasicVector<Type, Size>& ) const;
    BasicVector<Type, Size> operator * ( const BasicVector<Type, Size>& ) const;
    BasicVector<Type, Size> operator / ( const BasicVector<Type, Size>& ) const;

    BasicVector<Type, Size> operator + ( const Type& ) const;
    BasicVector<Type, Size> operator - ( const Type& ) const;
    BasicVector<Type, Size> operator * ( const Type& ) const;
    BasicVector<Type, Size> operator / ( const Type& ) const;

    BasicVector<Type, Size> operator - () const;

    const Type& operator [] ( size_t index ) const;
          Type& operator [] ( size_t index );

    template<class Length = float>
    Length getLength() const;

    template<class Length = float>
    Length getLengthSquared() const;

    // The following methods are applicable only to the vectors with floating
    // point element types
    void normalize();

    BasicVector<Type, Size> getNormalized() const;
};

template<class Type, size_t Size>
BasicVector<Type, Size> operator + (
    const Type&, const BasicVector<Type, Size>& );

template<class Type, size_t Size>
BasicVector<Type, Size> operator - (
    const Type&, const BasicVector<Type, Size>& );

template<class Type, size_t Size>
BasicVector<Type, Size> operator * (
    const Type&, const BasicVector<Type, Size>& );

template<class Type, size_t Size>
BasicVector<Type, Size> operator / (
    const Type&, const BasicVector<Type, Size>& );

template<class Type, size_t Size>
Type dotProduct(
    const BasicVector<Type, Size> &first,
    const BasicVector<Type, Size> &second );

template<class Type>
BasicVector<Type, 3> crossProduct(
    const BasicVector<Type, 3> &first,
    const BasicVector<Type, 3> &second );

using Vector = BasicVector<float, 3>;

using Vector2d = BasicVector<float, 2>;
using Vector3d = BasicVector<float, 3>;
using Vector4d = BasicVector<float, 4>;

using IntVector2d = BasicVector<int, 2>;
using IntVector3d = BasicVector<int, 3>;
using IntVector4d = BasicVector<int, 4>;

}

#include <storm/vector.inl>
