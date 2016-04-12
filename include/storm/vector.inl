#pragma once

#include <cmath>

namespace storm {

template<class Type>
const BasicVector<Type, 1> VectorBasis<Type, 1>::AxisX =
    BasicVector<Type, 1>( Type(1) );

template<class Type>
const BasicVector<Type, 2> VectorBasis<Type, 2>::AxisX =
    BasicVector<Type, 2>( Type(1), Type(0) );
template<class Type>
const BasicVector<Type, 2> VectorBasis<Type, 2>::AxisY =
    BasicVector<Type, 2>( Type(0), Type(1) );

template<class Type>
const BasicVector<Type, 3> VectorBasis<Type, 3>::AxisX =
    BasicVector<Type, 3>( Type(1), Type(0), Type(0) );
template<class Type>
const BasicVector<Type, 3> VectorBasis<Type, 3>::AxisY =
    BasicVector<Type, 3>( Type(0), Type(1), Type(0) );
template<class Type>
const BasicVector<Type, 3> VectorBasis<Type, 3>::AxisZ =
    BasicVector<Type, 3>( Type(0), Type(0), Type(1) );

template<class Type>
const BasicVector<Type, 4> VectorBasis<Type, 4>::AxisX =
    BasicVector<Type, 4>( Type(1), Type(0), Type(0), Type(0) );
template<class Type>
const BasicVector<Type, 4> VectorBasis<Type, 4>::AxisY =
    BasicVector<Type, 4>( Type(0), Type(1), Type(0), Type(0) );
template<class Type>
const BasicVector<Type, 4> VectorBasis<Type, 4>::AxisZ =
    BasicVector<Type, 4>( Type(0), Type(0), Type(1), Type(0) );
template<class Type>
const BasicVector<Type, 4> VectorBasis<Type, 4>::AxisW =
    BasicVector<Type, 4>( Type(0), Type(0), Type(0), Type(1) );

template<class Type, size_t Size>
inline BasicVector<Type, Size>::BasicVector() :
    VectorData {{0}}
{
}

template<class Type, size_t Size>
template<class... Values>
inline BasicVector<Type, Size>::BasicVector( Values... values ) :
    VectorData {{static_cast<Type>(values)...}}
{
    static_assert(
        sizeof...(Values) == Size,
        "The number of arguments must match the size of vector" );
}

// Mutating operators

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator += (
    const BasicVector<Type, Size> &vector )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] += vector[index];
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator -= (
    const BasicVector<Type, Size> &vector )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] -= vector[index];
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator *= (
    const BasicVector<Type, Size> &vector )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] *= vector[index];
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator /= (
    const BasicVector<Type, Size> &vector )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] /= vector[index];
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator += (
    const Type &value )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] += value;
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator -= (
    const Type &value )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] -= value;
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator *= (
    const Type &value )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] *= value;
    return *this;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size>& BasicVector<Type, Size>::operator /= (
    const Type &value )
{
    for( size_t index = 0; index < Size; ++index )
        elements[index] /= value;
    return *this;
}

// Non-mutating operators

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator + (
    const BasicVector<Type, Size> &vector ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] + vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator - (
    const BasicVector<Type, Size> &vector ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] - vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator * (
    const BasicVector<Type, Size> &vector ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] * vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator / (
    const BasicVector<Type, Size> &vector ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] / vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator + (
    const Type &value ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] + value;
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator - (
    const Type &value ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] - value;
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator * (
    const Type &value ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] * value;
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator / (
    const Type &value ) const
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = elements[index] / value;
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::operator - () const {
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = -elements[index];
    return result;
}

template<class Type, size_t Size>
const Type& BasicVector<Type, Size>::operator [] ( size_t index ) const {
    return elements[index];
}

template<class Type, size_t Size>
Type& BasicVector<Type, Size>::operator [] ( size_t index ) {
    return elements[index];
}

// Member functions

template<class Type, size_t Size>
template<class Length>
inline Length BasicVector<Type, Size>::getLength() const {
    return static_cast<Length>( std::sqrt(getLengthSquared()) );
}

template<class Type, size_t Size>
template<class Length>
inline Length BasicVector<Type, Size>::getLengthSquared() const {
    return static_cast<Length>( dotProduct(*this, *this) );
}

namespace detail {

template<class Type>
struct IsVectorNormalizationApplicable {
    static const bool Value = false;
};

template<>
struct IsVectorNormalizationApplicable<float> {
    static const bool Value = true;
};

template<>
struct IsVectorNormalizationApplicable<double> {
    static const bool Value = true;
};

} // namespace detail

template<class Type, size_t Size>
inline void BasicVector<Type, Size>::normalize() {
    static_assert(
        detail::IsVectorNormalizationApplicable<Type>::Value,
        "Vector normalization is applicable only to vectors with floating "
        "point element types" );

    const Type length = getLength<Type>();
    const Type lengthReciprocal = static_cast<Type>( 1 ) / length;

    if( isnormal(lengthReciprocal) )
        *this *= lengthReciprocal;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> BasicVector<Type, Size>::getNormalized() const {
    BasicVector<Type, Size> result = *this;
    result.normalize();
    return result;
}

// Non-member functions and operators

template<class Type, size_t Size>
inline Type dotProduct(
    const BasicVector<Type, Size> &first,
    const BasicVector<Type, Size> &second )
{
    Type result = Type();
    for( size_t index = 0; index < Size; ++index )
        result += first[index] * second[index];
    return result;
}

template<class Type>
inline BasicVector<Type, 3> crossProduct(
    const BasicVector<Type, 3> &first,
    const BasicVector<Type, 3> &second )
{
    return BasicVector<Type, 3>(
        first.y * second.z - first.z * second.y,
        first.z * second.x - first.x * second.z,
        first.x * second.y - first.y * second.x );
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> operator + (
    const Type &value, const BasicVector<Type, Size> &vector )
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = value + vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> operator - (
    const Type &value, const BasicVector<Type, Size> &vector )
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = value - vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> operator * (
    const Type &value, const BasicVector<Type, Size> &vector )
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = value * vector[index];
    return result;
}

template<class Type, size_t Size>
inline BasicVector<Type, Size> operator / (
    const Type &value, const BasicVector<Type, Size> &vector )
{
    BasicVector<Type, Size> result;
    for( size_t index = 0; index < Size; ++index )
        result[index] = value / vector[index];
    return result;
}

}
