#ifndef storm_ShaderOgl_h
#define storm_ShaderOgl_h

#include <Cg/cg.h>

#include "Noncopyable.h"
#include "Shader.h"

namespace storm {

class ShaderOgl : public Shader {
    NONCOPYABLE( ShaderOgl );
public:
    ShaderOgl( const std::string &sourceCode, Type type );
    
    virtual ~ShaderOgl() noexcept;
    
    virtual Uniform getUniform( const std::string &identifier ) const;
    
    CGprogram getProgram() const noexcept;

private:
    static CGprofile selectProfile( Type type );
    
    CGprogram _program;
};

}

#endif