#pragma once

#include <storm/noexcept.h>
#include <storm/noncopyable.h>
#include <storm/platform/ogl/api_ogl.h>

namespace storm {

class HandleOgl {
    NONCOPYABLE( HandleOgl );
public:
    HandleOgl() noexcept : _handle( 0 ) {
        return;
    }

    virtual ~HandleOgl() {
        return;
    }

    operator GLuint () const noexcept {
        return _handle;
    }

protected:
    GLuint _handle;
};

}
