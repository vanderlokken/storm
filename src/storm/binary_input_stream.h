#pragma once

#include <cstdint>
#include <fstream>
#include <type_traits>

namespace storm {

enum class ByteOrder {
    BigEndian,
    LittleEndian
};

inline ByteOrder getHostByteOrder() {
    const uint32_t value = 1;
    return *reinterpret_cast<const uint8_t*>( &value ) == 1 ?
        ByteOrder::LittleEndian : ByteOrder::BigEndian;
}

class BinaryInputStream {
public:
    explicit BinaryInputStream( std::istream &stream,
        ByteOrder dataByteOrder = ByteOrder::LittleEndian ) :
            _stream( stream ),
            _dataByteOrder( dataByteOrder ),
            _hostByteOrder( getHostByteOrder() )
    {
        _originalExceptionMask = _stream.exceptions();
        _stream.exceptions( std::ios_base::failbit );
    }

    BinaryInputStream( const BinaryInputStream& ) = delete;
    BinaryInputStream& operator = ( const BinaryInputStream& ) = delete;

    ~BinaryInputStream() {
        _stream.exceptions( _originalExceptionMask );
    }

    BinaryInputStream& read( void *data, std::streamsize count ) {
        _stream.read( static_cast<char*>(data), count );
        return *this;
    }

    template<class IntegralValue>
    IntegralValue read() {
        static_assert( std::is_integral<IntegralValue>::value,
            "Not an integral value" );

        IntegralValue value;
        _stream.read( reinterpret_cast<char*>(&value), sizeof(value) );

        if( _dataByteOrder == _hostByteOrder )
            return value;
        else
            return swapByteOrder( value );
    }

    std::istream& operator * () {
        return _stream;
    }

private:
    static uint8_t swapByteOrder( uint8_t value ) {
        return value;
    }
    static uint16_t swapByteOrder( uint16_t value ) {
        return (value >> 8) | (value << 8);
    }
    static uint32_t swapByteOrder( uint32_t value ) {
        return (value >> 24) | (value << 24) |
            ((value << 8) & 0x00FF0000) |
            ((value >> 8) & 0x0000FF00);
    }

    std::istream &_stream;
    std::ios_base::iostate _originalExceptionMask;

    ByteOrder _dataByteOrder;
    ByteOrder _hostByteOrder;
};

}
