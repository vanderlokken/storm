#pragma once

#include <exception>
#include <string>

#define throwRuntimeError( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwLogicError( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwInvalidArgument( description ) \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, description )

#define throwNotImplemented() \
    throw Exception( __FILE__, __LINE__, __FUNCTION__, "Not implemented" )

namespace storm {

class Exception : public std::exception {
public:
    Exception(
        const char *fileName, long line, const char *functionName,
        const std::string &description );

    virtual const char* what() const;

private:
    std::string _message;
};

}
