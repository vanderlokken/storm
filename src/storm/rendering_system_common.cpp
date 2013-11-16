#include <storm/rendering_system_common.h>

#include <array>

#include <storm/exception.h>
#include <storm/shader_cg.h>

namespace storm {

Shader::Pointer RenderingSystemCommon::getShader( Shader::Type shaderType ) const noexcept {
    switch( shaderType ) {
    case Shader::Type::Vertex:
        return _vertexShader;
    case Shader::Type::Pixel:
        return _pixelShader;
    case Shader::Type::Geometry:
        return _geometryShader;
    default:
        throwInvalidArgument( "'shaderType' is invalid" );
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
        throwInvalidArgument( "'shader' is invalid" );
    }
}

void RenderingSystemCommon::setShaderUniformValues() {

    std::array< Shader::Pointer, 3 > shaders = {
        _vertexShader,
        _pixelShader,
        _geometryShader
    };

    for( const auto &shader : shaders ) {
        auto shaderCg = std::static_pointer_cast< ShaderCg >( shader );
        if( shaderCg )
            shaderCg->updateUniformValues();
    }
    return;
}

}
