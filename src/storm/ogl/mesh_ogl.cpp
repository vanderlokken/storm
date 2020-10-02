#include <storm/ogl/mesh_ogl.h>

#include <storm/ogl/buffer_ogl.h>
#include <storm/ogl/vertex_format_ogl.h>
#include <storm/throw_exception.h>

namespace storm {

MeshOgl::MeshOgl(
        GpuContextOgl::Pointer gpuContext, const Description &description ) :
    _description( description ),
    _primitiveTopology(
        convertPrimitiveTopology(description.primitiveTopology) ),
    _handle( gpuContext )
{
    gpuContext->call<GlBindVertexArray>( _handle );

    const auto indexBuffer =
        std::dynamic_pointer_cast<BufferOgl>( _description.indexBuffer );
    const auto vertexBuffer =
        std::dynamic_pointer_cast<BufferOgl>( _description.vertexBuffer );
    const auto vertexFormat =
        std::dynamic_pointer_cast<VertexFormatOgl>( _description.vertexFormat );

    storm_assert(
        gpuContext == indexBuffer->getHandle().getGpuContext() );
    storm_assert(
        gpuContext == vertexBuffer->getHandle().getGpuContext() );

    gpuContext->call<GlBindBuffer>(
        GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getHandle() );

    gpuContext->call<GlBindBuffer>(
        GL_ARRAY_BUFFER, vertexBuffer->getHandle() );

    vertexFormat->install( *gpuContext );
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

std::shared_ptr<Mesh> Mesh::create(
    GpuContext::Pointer gpuContext, const Description &description )
{
    return std::make_shared<MeshOgl>(
        std::dynamic_pointer_cast<GpuContextOgl>(std::move(gpuContext)),
        description );
}

}
