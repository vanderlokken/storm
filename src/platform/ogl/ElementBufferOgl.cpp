#include "ElementBufferOgl.h"

#include <numeric>

#include "ConstantsOgl.h"
#include "CheckResultOgl.h"
#include "Exception.h"
#include "FunctionsOgl.h"
#include "IndexBufferOgl.h"
#include "VertexBufferOgl.h"

namespace storm {

ElementBufferHandleOgl::ElementBufferHandleOgl() {
    ::glGenVertexArrays( 1, &_handle );
    checkResult( "::glGenVertexArrays" );
    return;
}

ElementBufferHandleOgl::~ElementBufferHandleOgl() noexcept {
    ::glDeleteVertexArrays( 1, &_handle );
    return;
}

ElementBufferOgl::ElementBufferOgl( const Description &description )
    : _description( description ),
      _elementTopology( convertElementTopology(description.elementTopology) )
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

const ElementBuffer::Description& ElementBufferOgl::getDescription() const noexcept {
    return _description;
}

GLenum ElementBufferOgl::getElementTopology() const noexcept {
    return _elementTopology;
}

const ElementBufferHandleOgl& ElementBufferOgl::getHandle() const noexcept {
    return _handle;
}

void ElementBufferOgl::setVertexAttributes() {
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

GLenum ElementBufferOgl::convertElementTopology( ElementTopology elementTopology ) {
    GLenum result;

    switch( elementTopology ) {
    case ElementTopologyList:
        result = GL_TRIANGLES;
        break;

    case ElementTopologyStrip:
        result = GL_TRIANGLE_STRIP;
        break;

    default:
        throwInvalidArgument( "'elementTopology' is invalid" );
    }
    return result;
}

ElementBufferOgl::VertexAttributeFormat ElementBufferOgl::convertVertexAttributeFormat( Vertex::Attribute::Format format ) {
    VertexAttributeFormat result;

    switch( format ) {
    case Vertex::Attribute::FormatFloat:
        result.componentCount = 1;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format2Float:
        result.componentCount = 2;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format3Float:
        result.componentCount = 3;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format4Float:
        result.componentCount = 4;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format4Uint8:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format4Uint8Normalized:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format2Int16:
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format2Int16Normalized:
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format4Int16:
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Vertex::Attribute::Format4Int16Normalized:
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format2Uint16Normalized:
        result.componentCount = 2;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Vertex::Attribute::Format4Uint16Normalized:
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }
    return result;
}

std::shared_ptr<ElementBuffer> ElementBuffer::create( const Description &description ) {
    return std::make_shared< ElementBufferOgl >( description );
}

}