#pragma once

#include <Cg/cg.h>

#include <storm/noncopyable.h>
#include <storm/shader.h>

namespace storm {

class CGContextInstance {
public:
    static CGContextInstance getInstance();
    operator CGcontext () const;
private:
    CGContextInstance();
    std::shared_ptr<_CGcontext> _handle;
};

class ShaderCg : public Shader {
    NONCOPYABLE( ShaderCg );
public:
    virtual ~ShaderCg();

    virtual Type getType() const noexcept;
    virtual Uniform getUniform( const std::string &identifier ) const;

    CGprogram getProgram() const noexcept;

    void updateUniformValues();

protected:
    struct CompilerArguments {
        const char *sourceCode;
        const char **compilerOptions;
        CGprofile profile;
    };

    ShaderCg( CompilerArguments compilerArguments, Type type );

    Type _type;
    CGprogram _program;
    CGContextInstance _context;
};

void checkCgError( const std::string &call );

}
