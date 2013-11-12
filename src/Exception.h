#pragma once

#include <stdexcept>

#define throwRuntimeError( description ) \
    throw std::runtime_error( formatExceptionMessage(__FILE__, __LINE__, __FUNCTION__, description) )

#define throwLogicError( description ) \
    throw std::logic_error( formatExceptionMessage(__FILE__, __LINE__, __FUNCTION__, description) )

#define throwInvalidArgument( description ) \
    throw std::invalid_argument( formatExceptionMessage(__FILE__, __LINE__, __FUNCTION__, description) )

namespace storm {

const char* formatExceptionMessage(
    const char *fileName, long line, const char *functionName, const char *description );

}
