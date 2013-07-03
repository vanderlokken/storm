#ifndef storm_ShaderOgl_h
#define storm_ShaderOgl_h

#include "Noncopyable.h"
#include "ShaderCg.h"

namespace storm {

class ShaderOgl : public ShaderCg {
    NONCOPYABLE( ShaderOgl );
public:
    ShaderOgl( const std::string &sourceCode, Type type );

private:
    static CompilerArguments selectCompilerArguments(
        const std::string &sourceCode, Type type );
    static CGprofile selectProfile( Type type );
};

}

#endif