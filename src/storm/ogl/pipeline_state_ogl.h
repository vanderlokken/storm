#pragma once

#include <storm/pipeline_state.h>

namespace storm {

void switchOpenGlPipelineState(
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
