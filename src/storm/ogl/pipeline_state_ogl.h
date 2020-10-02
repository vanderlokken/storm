#pragma once

#include <storm/ogl/gpu_context_ogl.h>
#include <storm/pipeline_state.h>

namespace storm {

void switchOpenGlPipelineState(
    const GpuContextOgl &gpuContext,
    const PipelineState &previousState,
    const PipelineState &nextState );

class PipelineStateOgl : public PipelineState {
public:
    PipelineStateOgl( const Description& );

    const Description& getDescription() const override;

private:
    Description _description;
};

}
