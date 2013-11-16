#include <storm/platform/ogl/mesh_ogl.h>

#include <numeric>

#include <storm/exception.h>
#include <storm/platform/ogl/constants_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/functions_ogl.h>
#include <storm/platform/ogl/index_buffer_ogl.h>
#include <storm/platform/ogl/vertex_buffer_ogl.h>

namespace storm {

MeshHandleOgl::MeshHandleOgl() {
    ::glGenVertexArrays( 1, &_handle );
    checkResult( "::glGenVertexArrays" );
    return;
}

MeshHandleOgl::~MeshHandleOgl() {
    ::glDeleteVertexArrays( 1, &_handle );
    return;
}

MeshOgl::MeshOgl( const Description &description )
    : _description( description ),
      _triangleTopology( convertTriangleTopology(description.triangleTopology) )
{
    ::glBindVertexArray( _handle );
    checkResult( "::glBindVertexArray" );

    auto indexBuffer = std::static_pointer_cast< IndexBufferOgl >( _description.indexBuffer );
    auto vertexBuffer = std::static_pointer_cast< VertexBufferOgl >( _description.vertexBuffer );

    ::glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getHandle() );
    checkResult( "::glBindBuffer" );

    ::glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer->getHandle() );
    checkResult( "::glBindBuffer" );

    setVertexAttributes();
    return;
}

const Mesh::Description& MeshOgl::getDescription() const noexcept {
    return _description;
}

GLenum MeshOgl::getTriangleTopology() const noexcept {
    return _triangleTopology;
}

const MeshHandleOgl& MeshOgl::getHandle() const noexcept {
    return _handle;
}

void MeshOgl::setVertexAttributes() {
    const std::vector< Vertex::Attribute > &attributes = _description.vertexBuffer->getDescription().vertexAttributes;

    const size_t vertexSize = std::accumulate( attributes.cbegin(), attributes.cend(), 0,
        [](size_t size, Vertex::Attribute attribute) { return size + attribute.getSize(); } );

    const char *offset = 0;

    for( auto attribute = attributes.cbegin(); attribute != attributes.cend(); ++attribute ) {
        const GLuint index = attribute - attributes.cbegin();

        VertexAttributeFormat format = convertVertexAttributeFormat( attribute->format );

        const GLint componentCount = format.componentCount;
        const GLenum componentType = format.componentType;
        const GLboolean componentNormalized = format.componentNormalized;
        const GLsizei stride = vertexSize;

        ::glVertexAttribPointer( index, componentCount, componentType, componentNormalized, stride, offset );
        checkResult( "::glVertexAttribPointer" );

        ::glEnableVertexAttribArray( index );
        checkResult( "::glEnableVertexAttribArray" );

        offset += attribute->getSize();
    }
    return;
}

GLenum MeshOgl::convertTriangleTopology( TriangleTopology triangleTopology ) {
    switch( triangleTopology ) {
    case TriangleTopology::List:
        return GL_TRIANGLES;
    case TriangleTopology::Strip:
        return GL_TRIANGLE_STRIP;
    default:
        throwInvalidArgument( "'triangleTopology' is invalid" );
    }
}

MeshOgl::VertexAttributeFormat MeshOgl::convertVertexAttributeFormat( Vertex::Attribute::Format format ) {
    VertexAttributeFormat result;

    switch( format ) {
    case Vertex::Attribute::Format::Float:
        result.componentCount = 1;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector2Float:
        result.componentCount = 2;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector3Float:
        result.componentCount = 3;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector4Float:
        result.componentCount = 4;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector4Uint8:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector4Uint8Normalized:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format::Vector2Int16:
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector2Int16Normalized:
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format::Vector4Int16:
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format::Vector4Int16Normalized:
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format::Vector2Uint16Normalized:
        result.componentCount = 2;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format::Vector4Uint16Normalized:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }
    return result;
}

std::shared_ptr<Mesh> Mesh::create( const Description &description ) {
    return std::make_shared< MeshOgl >( description );
}

}
