#include <storm/platform/ogl/rasterization_technique_ogl.h>

#include <storm/throw_exception.h>

namespace storm {

RasterizationTechniqueOgl::RasterizationTechniqueOgl(
        const Description &description ) :
    _description( description ),
    _cullMode( convertCullMode(description.cullMode) ),
    _fillMode( convertFillMode(description.fillMode) )
{
}

const RasterizationTechnique::Description&
RasterizationTechniqueOgl::getDescription() const {
    return _description;
}

GLenum RasterizationTechniqueOgl::getCullMode() const {
    return _cullMode;
}

GLenum RasterizationTechniqueOgl::getFillMode() const {
    return _fillMode;
}

GLenum RasterizationTechniqueOgl::convertCullMode( CullMode cullMode ) {
    switch( cullMode ) {
    case CullMode::Nothing:
        // GL_NONE is not a valid argument for ::glCullFace. This value just
        // indicates that ::glDisable( GL_CULL_FACE ) should be called instead
        // of ::glCullFace.
        return GL_NONE;
    case CullMode::FrontFaces:
        return GL_FRONT;
    case CullMode::BackFaces:
        return GL_BACK;
    default:
        storm_assert_unreachable( "Unexpected cull mode value" );
        return 0;
    }
}

GLenum RasterizationTechniqueOgl::convertFillMode( FillMode fillMode ) {
    switch( fillMode ) {
    case FillMode::Solid:
        return GL_FILL;
    case FillMode::Wireframe:
        return GL_LINE;
    default:
        storm_assert_unreachable( "Unexpected fill mode value" );
        return 0;
    }
}

RasterizationTechnique::Pointer RasterizationTechnique::create(
    const Description &description )
{
    return std::make_shared< RasterizationTechniqueOgl >( description );
}

}
