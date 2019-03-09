#pragma once

#include <storm/rendering_system.h>

namespace storm {

class RenderingSystemCommon : public RenderingSystem {
public:
    Shader::Pointer getShader( Shader::Type ) const override;
    void setShader( Shader::Pointer ) override;
    void resetShader( Shader::Type ) override;

protected:
    Shader::Pointer _vertexShader;
    Shader::Pointer _pixelShader;
    Shader::Pointer _geometryShader;
};

}
