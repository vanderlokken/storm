#include <storm/platform/ogl/mesh_ogl.h>

#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/vertex_format_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

VertexArrayHandleOgl::VertexArrayHandleOgl() {
    ::glGenVertexArrays( 1, &_handle );
    checkResult( "::glGenVertexArrays" );
}

VertexArrayHandleOgl::~VertexArrayHandleOgl() {
    ::glDeleteVertexArrays( 1, &_handle );
}

MeshOgl::MeshOgl( const Description &description ) :
    _description( description ),
    _primitiveTopology(
        convertPrimitiveTopology(description.primitiveTopology) )
{
    ::glBindVertexArray( _handle );
    checkResult( "::glBindVertexArray" );

    const auto indexBuffer =
        std::static_pointer_cast<BufferOgl>( _description.indexBuffer );
    const auto vertexBuffer =
        std::static_pointer_cast<BufferOgl>( _description.vertexBuffer );
    const auto vertexFormat =
        std::static_pointer_cast<VertexFormatOgl>( _description.vertexFormat );

    ::glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getHandle() );
    checkResult( "::glBindBuffer" );

    ::glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer->getHandle() );
    checkResult( "::glBindBuffer" );

    vertexFormat->install();
}

const Mesh::Description& MeshOgl::getDescription() const {
    return _description;
}

GLenum MeshOgl::getPrimitiveTopology() const {
    return _primitiveTopology;
}

const VertexArrayHandleOgl& MeshOgl::getHandle() const {
    return _handle;
}

GLenum MeshOgl::convertPrimitiveTopology(
    PrimitiveTopology primitiveTopology )
{
    switch( primitiveTopology ) {
    case PrimitiveTopology::PointList:
        return GL_POINTS;
    case PrimitiveTopology::LineList:
        return GL_LINES;
    case PrimitiveTopology::LineStrip:
        return GL_LINE_STRIP;
    case PrimitiveTopology::TriangleList:
        return GL_TRIANGLES;
    case PrimitiveTopology::TriangleStrip:
        return GL_TRIANGLE_STRIP;
    default:
        storm_assert_unreachable( "Unexpected primitive topology value" );
        return 0;
    }
}

std::shared_ptr<Mesh> Mesh::create( const Description &description ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< MeshOgl >( description );
}

}
