#pragma once

#include <storm/rendering_system.h>

namespace storm {

class RenderingSystemCommon : public RenderingSystem {
public:

    virtual std::shared_ptr<Shader> getShader( Shader::Type ) const noexcept;
    virtual void setShader( std::shared_ptr<Shader> );

protected:
    void setShaderUniformValues();

    std::shared_ptr< Shader > _vertexShader;
    std::shared_ptr< Shader > _pixelShader;
    std::shared_ptr< Shader > _geometryShader;
};

}
