#pragma once

#include <exception>
#include <string>

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
