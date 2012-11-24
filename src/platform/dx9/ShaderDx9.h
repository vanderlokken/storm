#ifndef storm_ShaderDx9_h
#define storm_ShaderDx9_h

#include <map>
#include <vector>

#include <Cg/cg.h>

#include "Noncopyable.h"
#include "platform/win/ComPointer.h"
#include "Shader.h"

namespace storm {

class ShaderDx9 : public Shader {
    NONCOPYABLE( ShaderDx9 );
public:
    ShaderDx9( const std::string &sourceCode, Type type );
    virtual ~ShaderDx9() noexcept;
    
    virtual Uniform getUniform( const std::string &identifier ) const;
    
    CGprogram getProgram() const noexcept;
    
private:
    static CGprofile selectProfile( Type type );
    
    CGprogram _program;
};

}

#endif