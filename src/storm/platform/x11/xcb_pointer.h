#pragma once

#include <cstdlib>

namespace storm {

template <class T>
class XcbPointer {
public:
    XcbPointer( T *value ) :
        _value( value )
    {
    }

    XcbPointer(
        const XcbPointer<T>& ) = delete;
    XcbPointer<T>& operator = (
        const XcbPointer<T>& ) = delete;

    XcbPointer( XcbPointer<T> &&pointer ) {
        *this = std::move( pointer );
    }

    XcbPointer<T>& operator = ( XcbPointer<T> &&pointer ) {
        if( _value ) {
            free( _value );
        }

        _value = pointer._value;
        pointer._value = nullptr;
    }

    ~XcbPointer() {
        if( _value ) {
            free( _value );
        }
    }

    operator T* () const {
        return _value;
    }

    T& operator * () const {
        return *_value;
    }

    T* operator -> () const {
        return _value;
    }

private:
    T *_value = nullptr;
};

}
