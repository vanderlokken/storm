#pragma once

#include <cstddef>

namespace storm {

#ifdef _MSC_VER
// Disable MSVC warning "nonstandard extension used: nameless struct/union"
#pragma warning( push )
#pragma warning( disable : 4201 )
#endif

template<class Type, size_t Size>
struct VectorData {
    typedef struct {
        Type elements[Size];
    } Storage;
};

template<class Type>
struct VectorData<Type, 1> {
    typedef struct {
        union { Type elements[1]; struct {Type x;}; };
    } Storage;
};

template<class Type>
struct VectorData<Type, 2> {
    typedef struct {
        union { Type elements[2]; struct {Type x; Type y;}; };
    } Storage;
};

template<class Type>
struct VectorData<Type, 3> {
    typedef struct {
        union { Type elements[3]; struct {Type x; Type y; Type z;}; };
    } Storage;
};

template<class Type>
struct VectorData<Type, 4> {
    typedef struct {
        union { Type elements[4]; struct {Type x; Type y; Type z; Type w;}; };
    } Storage;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

template<class Type, size_t Size>
struct BasicVector;

template<class Type, size_t Size>
struct VectorBasis {};

template<class Type>
struct VectorBasis<Type, 1> {
    static const BasicVector<Type, 1> AxisX;
};

template<class Type>
struct VectorBasis<Type, 2> {
    static const BasicVector<Type, 2> AxisX;
    static const BasicVector<Type, 2> AxisY;
};

template<class Type>
struct VectorBasis<Type, 3> {
    static const BasicVector<Type, 3> AxisX;
    static const BasicVector<Type, 3> AxisY;
    static const BasicVector<Type, 3> AxisZ;
};

template<class Type>
struct VectorBasis<Type, 4> {
    static const BasicVector<Type, 4> AxisX;
    static const BasicVector<Type, 4> AxisY;
    static const BasicVector<Type, 4> AxisZ;
    static const BasicVector<Type, 4> AxisW;
};

template<class Type, size_t Size>
struct BasicVector : VectorData<Type, Size>::Storage, VectorBasis<Type, Size> {
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
