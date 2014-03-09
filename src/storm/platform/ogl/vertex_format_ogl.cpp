#include <storm/platform/ogl/vertex_format_ogl.h>

#include <storm/platform/ogl/check_result_ogl.h>

namespace storm {

VertexFormatOgl::VertexFormatOgl( const Description &description )
    : _description( description )
{
}

const VertexFormat::Description&
    VertexFormatOgl::getDescription() const
{
    return _description;
}

size_t VertexFormatOgl::getVertexSize() const {
    GLsizei vertexSize = 0;

    for( const auto &attribute : _description.attributes )
        vertexSize += getAttributeFormatDescription( attribute.format ).size;

    return vertexSize;
}

void VertexFormatOgl::install() const {
    const size_t vertexSize = getVertexSize();

    GLuint index = 0;
    const GLbyte *offset = 0;

    for( const auto &attribute : _description.attributes ) {
        const AttributeFormatDescription formatDescription =
            getAttributeFormatDescription( attribute.format );

        ::glVertexAttribPointer(
            index,
            formatDescription.componentCount,
            formatDescription.componentType,
            formatDescription.componentNormalized,
            vertexSize /* stride */, offset );
        checkResult( "::glVertexAttribPointer" );

        ::glEnableVertexAttribArray( index++ );
        checkResult( "::glEnableVertexAttribArray" );

        offset += formatDescription.size;
    }
}

VertexFormatOgl::AttributeFormatDescription
    VertexFormatOgl::getAttributeFormatDescription( Attribute::Format format )
{
    AttributeFormatDescription result;

    switch( format ) {
    case Attribute::Format::Float:
        result.size = 4;
        result.componentCount = 1;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector2Float:
        result.size = 8;
        result.componentCount = 2;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector3Float:
        result.size = 12;
        result.componentCount = 3;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector4Float:
        result.size = 16;
        result.componentCount = 4;
        result.componentType = GL_FLOAT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector4Uint8:
        result.size = 4;
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector4Uint8Normalized:
        result.size = 4;
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_BYTE;
        result.componentNormalized = GL_TRUE;
        break;

    case Attribute::Format::Vector2Int16:
        result.size = 4;
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector2Int16Normalized:
        result.size = 4;
        result.componentCount = 2;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Attribute::Format::Vector4Int16:
        result.size = 8;
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_FALSE;
        break;

    case Attribute::Format::Vector4Int16Normalized:
        result.size = 8;
        result.componentCount = 4;
        result.componentType = GL_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Attribute::Format::Vector2Uint16Normalized:
        result.size = 4;
        result.componentCount = 2;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    case Attribute::Format::Vector4Uint16Normalized:
        result.size = 8;
        result.componentCount = 4;
        result.componentType = GL_UNSIGNED_SHORT;
        result.componentNormalized = GL_TRUE;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }

    return result;
}

VertexFormat::Pointer VertexFormat::create(
    const VertexFormat::Description &description )
{
    return std::make_shared<VertexFormatOgl>( description );
}

}
