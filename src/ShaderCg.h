#pragma once

#include <Cg/cg.h>

#include "Noncopyable.h"
#include "Shader.h"

namespace storm {

class ShaderCg : public Shader {
    NONCOPYABLE( ShaderCg );
public:
    virtual ~ShaderCg() noexcept;

    virtual Type getType() const noexcept;
    virtual Uniform getUniform( const std::string &identifier ) const;

    CGprogram getProgram() const noexcept;

    void updateUniformValues();

protected:
    ShaderCg( Type type, CGprofile cgProfile,
        const std::string &sourceCode, const char **compilerOptions );

    Type _type;
    CGprogram _program;
};

CGcontext getCgContext();

void checkCgError( const std::string &call );

}
