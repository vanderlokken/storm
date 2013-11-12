#pragma once

#include "Noncopyable.h"
#include "ShaderCg.h"

namespace storm {

class ShaderDx9 : public ShaderCg {
    NONCOPYABLE( ShaderDx9 );
public:
    ShaderDx9( const std::string &sourceCode, Type type );

private:
    static CompilerArguments selectCompilerArguments(
        const std::string &sourceCode, Type type );
    static CGprofile selectProfile( Type type );
};

}
