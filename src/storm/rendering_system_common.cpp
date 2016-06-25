#include <storm/rendering_system_common.h>

#include <storm/throw_exception.h>

namespace storm {

Shader::Pointer RenderingSystemCommon::getShader(
    Shader::Type shaderType ) const
{
    switch( shaderType ) {
    case Shader::Type::Vertex:
        return _vertexShader;
    case Shader::Type::Pixel:
        return _pixelShader;
    case Shader::Type::Geometry:
        return _geometryShader;
    default:
        storm_assert_unreachable( "Unexpected shader type value" );
        return nullptr;
    }
}

void RenderingSystemCommon::setShader( Shader::Pointer shader ) {
    switch( shader->getType() ) {
    case Shader::Type::Vertex:
        _vertexShader = shader;
        break;
    case Shader::Type::Pixel:
        _pixelShader = shader;
        break;
    case Shader::Type::Geometry:
        _geometryShader = shader;
        break;
    default:
        storm_assert_unreachable( "Unexpected shader type value" );
    }
}

void RenderingSystemCommon::resetShader( Shader::Type shaderType ) {
    switch( shaderType ) {
    case Shader::Type::Vertex:
        _vertexShader.reset();
        break;
    case Shader::Type::Pixel:
        _pixelShader.reset();
        break;
    case Shader::Type::Geometry:
        _geometryShader.reset();
        break;
    default:
        storm_assert_unreachable( "Unexpected shader type value" );
    }
}

}
