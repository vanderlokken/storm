#pragma once

#include <exception>
#include <string>

namespace storm {

class Exception : public std::exception {
public:
    Exception() = default;
    Exception(
        const char *fileName, long line, const char *functionName,
        const std::string &description );

    explicit Exception( const std::string &description );

#ifndef _MSC_VER
    virtual const char* what() const noexcept( true );
#else
    virtual const char* what() const;
#endif

    Exception& operator << ( const std::string &message );

private:
    std::string _message;
};

class SystemRequirementsNotMet : public Exception {};
class ResourceLoadingError : public Exception {};

}
