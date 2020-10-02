#pragma once

#include <storm/ogl/gpu_context_ogl.h>

namespace storm {

template <class CreationApiFunction, class DestructionApiFunction>
class HandleOgl {
public:
    explicit HandleOgl( const GpuContextOgl::Pointer &gpuContext ) :
        _gpuContext( gpuContext )
    {
        gpuContext->call<CreationApiFunction>( 1, &_handle );
    }

    HandleOgl(
        const HandleOgl& ) = delete;
    HandleOgl& operator = (
        const HandleOgl& ) = delete;

    ~HandleOgl() {
        if( const GpuContextOgl::Pointer gpuContext = _gpuContext.tryLock() ) {
            gpuContext->callUnchecked<DestructionApiFunction>( 1, &_handle );
        }
    }

    GpuContextOgl::Pointer getGpuContext() const {
        return _gpuContext.locked();
    }

    const WeakGpuContextOgl& getWeakGpuContext() const {
        return _gpuContext;
    }

    operator GLuint () const {
        return _handle;
    }

private:
    WeakGpuContextOgl _gpuContext;
    GLuint _handle = 0;
};

}
