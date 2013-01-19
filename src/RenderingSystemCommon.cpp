#include "RenderingSystemCommon.h"

#include <array>

#include "Exception.h"
#include "ShaderCg.h"

namespace storm {

std::shared_ptr<Shader> RenderingSystemCommon::getShader( Shader::Type shaderType ) const noexcept {
    switch( shaderType ) {
    case Shader::TypeVertex:
        return _vertexShader;
    case Shader::TypePixel:
        return _pixelShader;
    case Shader::TypeGeometry:
        return _geometryShader;
    default:
        throwInvalidArgument( "'shaderType' is invalid" );
    }
}

void RenderingSystemCommon::setShader( std::shared_ptr<Shader> shader ) {
    switch( shader->getType() ) {
    case Shader::TypeVertex:
        _vertexShader = shader;
        break;
    case Shader::TypePixel:
        _pixelShader = shader;
        break;
    case Shader::TypeGeometry:
        _geometryShader = shader;
        break;
    default:
        throwInvalidArgument( "'shader' is invalid" );
    }
}

void RenderingSystemCommon::setShaderUniformValues() {

    std::array< std::shared_ptr<Shader>, 3 > shaders = {
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
