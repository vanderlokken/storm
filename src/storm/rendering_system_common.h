#pragma once

#include <storm/rendering_system.h>

namespace storm {

class RenderingSystemCommon : public RenderingSystem {
public:

    virtual Shader::Pointer getShader( Shader::Type ) const;
    virtual void setShader( Shader::Pointer );

protected:
    Shader::Pointer _vertexShader;
    Shader::Pointer _pixelShader;
    Shader::Pointer _geometryShader;
};

}
