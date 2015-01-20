#include <storm/mesh.h>

#include <vector>

#include <storm/binary_input_stream.h>
#include <storm/exception.h>

namespace storm {

namespace {

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

} // namespace

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
