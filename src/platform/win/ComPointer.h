#ifndef storm_ComPointer_h
#define storm_ComPointer_h

#include "Noexcept.h"

namespace storm {

template< class T > class ComPointer {
public:
    ComPointer() noexcept : _pointer( nullptr ) { }
    ComPointer( const ComPointer& ) noexcept;
    ~ComPointer() noexcept { if( _pointer ) _pointer->Release(); }

    ComPointer& operator = ( const ComPointer& ) noexcept;

    bool operator ! () noexcept { return !_pointer; }

    bool operator == ( const ComPointer& ) noexcept;
    bool operator != ( const ComPointer& ) noexcept;

    T* get() const noexcept { return _pointer; }
    T* operator -> () const noexcept { return _pointer; }

    T** getAddress() noexcept { return &_pointer; }

private:
    T *_pointer;
};

template< class T > ComPointer< T >::ComPointer( const ComPointer< T > &comPointer ) noexcept
    : _pointer( comPointer._pointer )
{
    if( _pointer ) {
        _pointer->AddRef();
    }
    return;
}

template< class T > ComPointer< T >& ComPointer< T >::operator = ( const ComPointer< T > &comPointer ) noexcept {
    T *pointer = comPointer._pointer;

    if( pointer ) {
        pointer->AddRef();
    }
    if( _pointer ) {
        _pointer->Release();
    }
    _pointer = pointer;
    return *this;
}

template<class T> bool ComPointer<T>::operator == ( const ComPointer<T> &comPointer ) noexcept {
    return _pointer == comPointer._pointer;
}

template<class T> bool ComPointer<T>::operator != ( const ComPointer<T> &comPointer ) noexcept {
    return _pointer != comPointer._pointer;
}

}

#endif