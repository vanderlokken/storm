#pragma once

#include <storm/platform/ogl/api_ogl.h>

namespace storm {

class HandleOgl {
public:
    HandleOgl() :
        _handle( 0 )
    {
    }

    HandleOgl(
        const HandleOgl& ) = delete;
    HandleOgl& operator = (
        const HandleOgl& ) = delete;

    virtual ~HandleOgl() {}

    operator GLuint () const {
        return _handle;
    }

protected:
    GLuint _handle;
};

}
