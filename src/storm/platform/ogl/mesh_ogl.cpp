#include <storm/platform/ogl/mesh_ogl.h>

#include <storm/platform/ogl/buffer_ogl.h>
#include <storm/platform/ogl/check_result_ogl.h>
#include <storm/platform/ogl/rendering_system_ogl.h>
#include <storm/platform/ogl/vertex_format_ogl.h>
#include <storm/throw_exception.h>

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

    return;
}

const Mesh::Description& MeshOgl::getDescription() const {
    return _description;
}

GLenum MeshOgl::getTriangleTopology() const {
    return _triangleTopology;
}

const MeshHandleOgl& MeshOgl::getHandle() const {
    return _handle;
}

GLenum MeshOgl::convertTriangleTopology( TriangleTopology triangleTopology ) {
    switch( triangleTopology ) {
    case TriangleTopology::List:
        return GL_TRIANGLES;
    case TriangleTopology::Strip:
        return GL_TRIANGLE_STRIP;
    default:
        storm_assert_unreachable( "Unexpected triangle topology value" );
        return 0;
    }
}

std::shared_ptr<Mesh> Mesh::create( const Description &description ) {
    RenderingSystemOgl::installOpenGlContext();

    return std::make_shared< MeshOgl >( description );
}

}
