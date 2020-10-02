#include <storm/ogl/pipeline_state_ogl.h>

#include <algorithm>

#include <storm/ogl/api_functions_ogl.h>
#include <storm/ogl/condition_ogl.h>

namespace storm {

namespace {

using StateDescription = PipelineState::Description;

GLenum convert( BlendingOperation operation ) {
    static const GLenum values[] = {
        GL_FUNC_ADD,
        GL_FUNC_SUBTRACT,
        GL_FUNC_REVERSE_SUBTRACT,
        GL_MIN,
        GL_MAX
    };

    return values[static_cast<size_t>(operation)];
}

GLenum convert( BlendingFactor factor ) {
    static const GLenum values[] = {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
        GL_SRC_ALPHA_SATURATE
    };

    return values[static_cast<size_t>(factor)];
}

GLenum convert( PrimitiveCullMode cullMode ) {
    static const GLenum values[] = {
        // GL_NONE is not a valid argument for ::glCullFace. This value just
        // indicates that ::glDisable( GL_CULL_FACE ) should be called instead
        // of ::glCullFace.
        GL_NONE,
        GL_FRONT,
        GL_BACK
    };

    return values[static_cast<size_t>(cullMode)];
}

GLenum convert( PrimitiveFillMode fillMode ) {
    static const GLenum values[] = {
        GL_FILL,
        GL_LINE
    };

    return values[static_cast<size_t>(fillMode)];
}

GLenum convert( StencilOperation operation ) {
    static const GLenum values[] = {
        GL_ZERO,
        GL_KEEP,
        GL_REPLACE,
        GL_INCR_WRAP,
        GL_DECR_WRAP,
        GL_INCR,
        GL_DECR,
        GL_INVERT
    };

    return values[static_cast<size_t>(operation)];
}

void switchBlendingState(
    const GpuContextOgl &gpuContext,
    const std::optional<BlendingState> &previousState,
    const std::optional<BlendingState> &state )
{
    if( previousState.has_value() != state.has_value() ) {
        setBooleanOpenGlState( gpuContext, GL_BLEND, state.has_value() );
    }

    if( state ) {
        const bool operationsPreserved =
            previousState &&
            previousState->colorBlending.operation ==
                state->colorBlending.operation &&
            previousState->alphaBlending.operation ==
                state->alphaBlending.operation;

        if( !operationsPreserved ) {
            gpuContext.call<GlBlendEquationSeparate>(
                convert(state->colorBlending.operation),
                convert(state->alphaBlending.operation) );
        }

        const bool factorsPreserved =
            previousState &&
            previousState->colorBlending.sourceFactor ==
                state->colorBlending.sourceFactor &&
            previousState->colorBlending.targetFactor ==
                state->colorBlending.targetFactor &&
            previousState->alphaBlending.sourceFactor ==
                state->alphaBlending.sourceFactor &&
            previousState->alphaBlending.targetFactor ==
                state->alphaBlending.targetFactor;

        if( !factorsPreserved ) {
            gpuContext.call<GlBlendFuncSeparate>(
                convert(state->colorBlending.sourceFactor),
                convert(state->colorBlending.targetFactor),
                convert(state->alphaBlending.sourceFactor),
                convert(state->alphaBlending.targetFactor) );
        }
    }
}

void switchRasterizationState(
    const GpuContextOgl &gpuContext,
    const StateDescription &previousState,
    const StateDescription &state )
{
    auto isUpdateRequired = [&]( auto member ) {
        return previousState.*member != state.*member;
    };

    if( isUpdateRequired(&StateDescription::primitiveCullMode) ) {
        if( state.primitiveCullMode != PrimitiveCullMode::Nothing ) {
            setBooleanOpenGlState( gpuContext, GL_CULL_FACE, true );

            gpuContext.call<GlCullFace>( convert(state.primitiveCullMode) );
        } else {
            setBooleanOpenGlState( gpuContext, GL_CULL_FACE, false );
        }
    }

    if( isUpdateRequired(&StateDescription::primitiveFillMode) ) {
        gpuContext.call<GlPolygonMode>(
            GL_FRONT_AND_BACK, convert(state.primitiveFillMode) );
    }

    if( isUpdateRequired(&StateDescription::rectangleClippingEnabled) ) {
        setBooleanOpenGlState(
            gpuContext, GL_SCISSOR_TEST, state.rectangleClippingEnabled );
    }

    if( isUpdateRequired(&StateDescription::depthClippingEnabled) ) {
        setBooleanOpenGlState(
            gpuContext, GL_DEPTH_CLAMP, !state.depthClippingEnabled );
    }

    if( isUpdateRequired(&StateDescription::depthBiasSlopeFactor) ||
        isUpdateRequired(&StateDescription::depthBiasConstantFactor) )
    {
        gpuContext.call<GlPolygonOffset>(
            static_cast<GLfloat>(state.depthBiasSlopeFactor),
            static_cast<GLfloat>(state.depthBiasConstantFactor) );
    }

    if( isUpdateRequired(&StateDescription::clippingDistanceArraySize) ) {
        const size_t minClippingDistanceArraySize = std::min(
            state.clippingDistanceArraySize,
            previousState.clippingDistanceArraySize );

        const size_t maxClippingDistanceArraySize = std::max(
            state.clippingDistanceArraySize,
            previousState.clippingDistanceArraySize );

        for( size_t index = minClippingDistanceArraySize;
                index < maxClippingDistanceArraySize; ++index ) {
            const bool enabled = index < state.clippingDistanceArraySize;

            setBooleanOpenGlState(
                gpuContext,
                static_cast<GLenum>(GL_CLIP_DISTANCE0 + index), enabled );
        }
    }
}

void switchDepthStencilState(
    const GpuContextOgl &gpuContext,
    const StateDescription &previousState,
    const StateDescription &state )
{
    if( state.depthTest.has_value() !=
            previousState.depthTest.has_value() ) {
        setBooleanOpenGlState(
            gpuContext, GL_DEPTH_TEST, state.depthTest.has_value() );
    }

    if( state.stencilTest.has_value() !=
            previousState.stencilTest.has_value() ) {
        setBooleanOpenGlState(
            gpuContext, GL_STENCIL_TEST, state.stencilTest.has_value() );
    }

    if( state.depthTest ) {
        const bool conditionPreserved =
            previousState.depthTest &&
            previousState.depthTest->passCondition ==
                state.depthTest->passCondition;

        if( !conditionPreserved ) {
            gpuContext.call<GlDepthFunc>(
                convertCondition(state.depthTest->passCondition) );
        }
    }

    // TODO: track unnecessary state changes
    if( const std::optional<StencilTest> &test = state.stencilTest ) {
        gpuContext.call<GlStencilOpSeparate>(
            GL_FRONT,
            convert(test->algorithmForFrontFaces.operationOnStencilTestFail),
            convert(test->algorithmForFrontFaces.operationOnDepthTestFail),
            convert(test->algorithmForFrontFaces.operationOnDepthTestPass) );

        gpuContext.call<GlStencilOpSeparate>(
            GL_BACK,
            convert(test->algorithmForBackFaces.operationOnStencilTestFail),
            convert(test->algorithmForBackFaces.operationOnDepthTestFail),
            convert(test->algorithmForBackFaces.operationOnDepthTestPass) );

        gpuContext.call<GlStencilFuncSeparate>(
            GL_FRONT,
            convertCondition(test->algorithmForFrontFaces.passCondition),
            test->referenceValue,
            test->mask );

        gpuContext.call<GlStencilFuncSeparate>(
            GL_BACK,
            convertCondition(test->algorithmForBackFaces.passCondition),
            test->referenceValue,
            test->mask );
    }

    if( previousState.writeDepthValues != state.writeDepthValues ) {
        gpuContext.call<GlDepthMask>( state.writeDepthValues );
    }
}

} // namespace

void switchOpenGlPipelineState(
    const GpuContextOgl &gpuContext,
    const PipelineState &previousState,
    const PipelineState &nextState )
{
    const PipelineState::Description &previousStateDescription =
        previousState.getDescription();
    const PipelineState::Description &nextStateDescription =
        nextState.getDescription();

    switchBlendingState(
        gpuContext,
        previousStateDescription.blendingState,
        nextStateDescription.blendingState );
    switchRasterizationState(
        gpuContext, previousStateDescription, nextStateDescription );
    switchDepthStencilState(
        gpuContext, previousStateDescription, nextStateDescription );
}

PipelineStateOgl::PipelineStateOgl( const Description &description ) :
    _description( description )
{
}

const PipelineState::Description& PipelineStateOgl::getDescription() const {
    return _description;
}

PipelineState::Pointer PipelineState::create( const Description &description ) {
    return std::make_shared<PipelineStateOgl>( description );
}

}
