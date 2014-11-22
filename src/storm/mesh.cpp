#include <storm/mesh.h>

#include <cstdint>
#include <fstream>
#include <type_traits>
#include <vector>

#include <storm/exception.h>

namespace storm {

namespace {

class BinaryInputStream {
public:
    enum class ByteOrder {
        BigEndian,
        LittleEndian
    };

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

    BinaryInputStream& read( char *data, std::streamsize count ) {
        _stream.read( data, count );
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

private:
    static ByteOrder getHostByteOrder() {
        const uint32_t value = 1;
        return *reinterpret_cast<const uint8_t*>( &value ) == 1 ?
            ByteOrder::LittleEndian : ByteOrder::BigEndian;
    }

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

Mesh::Pointer parse( BinaryInputStream &stream ) {
    const uint32_t attributeCount = stream.read<uint32_t>();

    typedef VertexFormat::Attribute VertexAttribute;

    std::vector<VertexAttribute> attributes( attributeCount );
    for( auto &attribute : attributes ) {
        const uint32_t semantics = stream.read<uint32_t>();
        const uint32_t format = stream.read<uint32_t>();

        attribute.semantics =
            static_cast<VertexAttribute::Semantics>( semantics );
        attribute.format =
            static_cast<VertexAttribute::Format>( format );
    }

    const uint8_t vertexSize = stream.read<uint8_t>();
    const uint32_t vertexDataSize = stream.read<uint32_t>();

    std::vector<char> vertexData( vertexDataSize );
    stream.read( vertexData.data(), vertexDataSize );

    const uint8_t indexSize = stream.read<uint8_t>();
    const uint32_t indexDataSize = stream.read<uint32_t>();

    std::vector<char> indexData( indexDataSize );
    stream.read( indexData.data(), indexDataSize );

    VertexFormat::Pointer vertexFormat =
        VertexFormat::create( {attributes, vertexSize} );

    Buffer::Description vertexBufferDescription;
    vertexBufferDescription.size = vertexDataSize;
    vertexBufferDescription.elementSize = vertexSize;
    vertexBufferDescription.resourceType = ResourceType::Static;

    Buffer::Description indexBufferDescription;
    indexBufferDescription.size = indexDataSize;
    indexBufferDescription.elementSize = indexSize;
    indexBufferDescription.resourceType = ResourceType::Static;

    Mesh::Description meshDescription;
    meshDescription.vertexFormat = vertexFormat;
    meshDescription.vertexBuffer =
        Buffer::create( vertexBufferDescription, vertexData.data() );
    meshDescription.indexBuffer =
        Buffer::create( indexBufferDescription, indexData.data() );
    meshDescription.primitiveTopology = Mesh::PrimitiveTopology::TriangleList;

    return Mesh::create( meshDescription );
}

}

Mesh::Pointer Mesh::load( std::istream &stream ) {
    try {
        BinaryInputStream binaryInputStream( stream );
        return parse( binaryInputStream );
    } catch( std::ios_base::failure& ) {
        throw ResourceLoadingError() << "Invalid mesh data";
    }
}

Mesh::Pointer Mesh::load( const std::string &filename ) {
    std::ifstream stream( filename, std::ios::binary );

    if( !stream )
        throw ResourceLoadingError() << "Couldn't open " << filename;

    return Mesh::load( stream );
}

}
