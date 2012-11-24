#ifndef storm_ShaderOperators_h
#define storm_ShaderOperators_h

#include <istream>
#include <memory>

#include "Shader.h"

namespace storm {

std::shared_ptr< Shader > readShader( std::istream &stream, Shader::Type shaderType );

}

#endif