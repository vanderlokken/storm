#ifndef storm_ShaderOgl_h
#define storm_ShaderOgl_h

#include <map>

#include "CoreTypesOgl.h"
#include "Noncopyable.h"
#include "Shader.h"

namespace storm {

class ShaderOgl : public Shader {
    NONCOPYABLE( ShaderOgl );
public:
    ShaderOgl( const std::string &sourceCode );
    
    virtual ~ShaderOgl() noexcept;
    
    virtual void setUniformValue( UniformIdentifier identifier, float value );
    
    virtual void setUniformValue( UniformIdentifier identifier, const Color &value );
    virtual void setUniformValue( UniformIdentifier identifier, const Vector &value );
    virtual void setUniformValue( UniformIdentifier identifier, const Matrix &value );
    
    virtual void setUniformValue( UniformIdentifier identifier, std::shared_ptr<Sampler> value );
    virtual void setUniformValue( UniformIdentifier identifier, std::shared_ptr<Texture> value );
    
    GLuint getProgram() const noexcept;
    
private:
    GLint getUniformLocation( UniformIdentifier identifier );
    
    GLuint _program;
    GLuint _vertexShader;
    GLuint _pixelShader;
    
    std::map< UniformIdentifier, GLint > _locations;
};

}

#endif