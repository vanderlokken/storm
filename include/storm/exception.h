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

    virtual const char* what() const;

    Exception& operator << ( const std::string &message );

private:
    std::string _message;
};

class SystemRequirementsNotMet : public Exception {};

}
