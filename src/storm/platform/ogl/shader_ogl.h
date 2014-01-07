#pragma once

#include <storm/noncopyable.h>
#include <storm/platform/ogl/handle_ogl.h>
#include <storm/shader.h>

namespace storm {

class ProgramHandleOgl : public HandleOgl {
public:
    ProgramHandleOgl( GLenum shaderType, const char *sourceCode );
    ~ProgramHandleOgl();
};

class ShaderOgl :
    public Shader, public std::enable_shared_from_this< ShaderOgl > {
        NONCOPYABLE( ShaderOgl );
public:
    ShaderOgl( const std::string &sourceCode, Type type );

    virtual Type getType() const noexcept;
    virtual Uniform getUniform( const std::string &identifier ) const;

    const ProgramHandleOgl& getHandle() const;

private:
    static GLenum convertType( Type );

    Type _type;
    ProgramHandleOgl _handle;
};

}
