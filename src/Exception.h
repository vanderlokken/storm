#ifndef storm_Exception_h
#define storm_Exception_h

#include <stdexcept>

#define throwRuntimeError( description ) \
    throwException< std::runtime_error >( __FILE__, __LINE__, __FUNCTION__, description )

#define throwLogicError( description ) \
    throwException< std::logic_error >( __FILE__, __LINE__, __FUNCTION__, description )

#define throwInvalidArgument( description ) \
    throwException< std::invalid_argument >( __FILE__, __LINE__, __FUNCTION__, description )

namespace storm {

template< class ExceptionType > void throwException(
    const char *fileName, long line, const char *functionName, const char *description );

}

#endif