#pragma once

#include <storm/platform/ogl/api_ogl.h>

namespace storm {

class HandleOgl {
public:
    HandleOgl() : _handle( 0 ) {
        return;
    }

    HandleOgl(
        const HandleOgl& ) = delete;
    HandleOgl& operator = (
        const HandleOgl& ) = delete;

    virtual ~HandleOgl() {
        return;
    }

    operator GLuint () const {
        return _handle;
    }

protected:
    GLuint _handle;
};

}
