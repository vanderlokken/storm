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
    static CGprofile selectProfile( Type type );
    static const char** selectCompilerOptions( Type type );
};

}

#endif