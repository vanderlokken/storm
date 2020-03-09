#include <storm/ogl/pipeline_state_ogl.h>

#include <storm/ogl/api_ogl.h>
#include <storm/ogl/check_result_ogl.h>
#include <storm/ogl/condition_ogl.h>
#include <storm/ogl/rendering_system_ogl.h>

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
    const std::optional<BlendingState> &previousState,
    const std::optional<BlendingState> &state )
{
    if( previousState.has_value() != state.has_value() ) {
        setBooleanOpenGlState( GL_BLEND, state.has_value() );
    }

    if( state ) {
        const bool operationsPreserved =
            previousState &&
            previousState->colorBlending.operation ==
                state->colorBlending.operation &&
            previousState->alphaBlending.operation ==
                state->alphaBlending.operation;

        if( !operationsPreserved ) {
            ::glBlendEquationSeparate(
                convert(state->colorBlending.operation),
                convert(state->alphaBlending.operation) );
            checkResult( "::glBlendEquationSeparate" );
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
            ::glBlendFuncSeparate(
                convert(state->colorBlending.sourceFactor),
                convert(state->colorBlending.targetFactor),
                convert(state->alphaBlending.sourceFactor),
                convert(state->alphaBlending.targetFactor) );
            checkResult( "::glBlendFuncSeparate" );
        }
    }
}

void switchRasterizationState(
    const StateDescription &previousState,
    const StateDescription &state )
{
    auto isUpdateRequired = [&]( auto member ) {
        return previousState.*member != state.*member;
    };

    if( isUpdateRequired(&StateDescription::primitiveCullMode) ) {
        if( state.primitiveCullMode != PrimitiveCullMode::Nothing ) {
            setBooleanOpenGlState( GL_CULL_FACE, true );

            ::glCullFace( convert(state.primitiveCullMode) );
            checkResult( "::glCullFace" );
        } else {
            setBooleanOpenGlState( GL_CULL_FACE, false );
        }
    }

    if( isUpdateRequired(&StateDescription::primitiveFillMode) ) {
        ::glPolygonMode( GL_FRONT_AND_BACK, convert(state.primitiveFillMode) );
        checkResult( "::glPolygonMode" );
    }

    if( isUpdateRequired(&StateDescription::rectangleClippingEnabled) ) {
        setBooleanOpenGlState(
            GL_SCISSOR_TEST, state.rectangleClippingEnabled );
    }

    if( isUpdateRequired(&StateDescription::depthClippingEnabled) ) {
        setBooleanOpenGlState(
            GL_DEPTH_CLAMP, !state.depthClippingEnabled );
    }

    if( isUpdateRequired(&StateDescription::depthBiasSlopeFactor) ||
        isUpdateRequired(&StateDescription::depthBiasConstantFactor) )
    {
        ::glPolygonOffset(
            static_cast<GLfloat>(state.depthBiasSlopeFactor),
            static_cast<GLfloat>(state.depthBiasConstantFactor) );
        checkResult( "::glPolygonOffset" );
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
                static_cast<GLenum>(GL_CLIP_DISTANCE0 + index), enabled );
        }
    }
}

void switchDepthStencilState(
    const StateDescription &previousState,
    const StateDescription &state )
{
    if( state.depthTest.has_value() !=
            previousState.depthTest.has_value() ) {
        setBooleanOpenGlState( GL_DEPTH_TEST, state.depthTest.has_value() );
    }

    if( state.stencilTest.has_value() !=
            previousState.stencilTest.has_value() ) {
        setBooleanOpenGlState( GL_STENCIL_TEST, state.stencilTest.has_value() );
    }

    if( state.depthTest ) {
        const bool conditionPreserved =
            previousState.depthTest &&
            previousState.depthTest->passCondition ==
                state.depthTest->passCondition;

        if( !conditionPreserved ) {
            ::glDepthFunc( convertCondition(state.depthTest->passCondition) );
            checkResult( "::glDepthFunc" );
        }
    }

    // TODO: track unnecessary state changes
    if( const std::optional<StencilTest> &test = state.stencilTest ) {
        ::glStencilOpSeparate(
            GL_FRONT,
            convert(test->algorithmForFrontFaces.operationOnStencilTestFail),
            convert(test->algorithmForFrontFaces.operationOnDepthTestFail),
            convert(test->algorithmForFrontFaces.operationOnDepthTestPass) );
        checkResult( "::glStencilOpSeparate" );

        ::glStencilOpSeparate(
            GL_BACK,
            convert(test->algorithmForBackFaces.operationOnStencilTestFail),
            convert(test->algorithmForBackFaces.operationOnDepthTestFail),
            convert(test->algorithmForBackFaces.operationOnDepthTestPass) );
        checkResult( "::glStencilOpSeparate" );

        ::glStencilFuncSeparate(
            GL_FRONT,
            convertCondition(test->algorithmForFrontFaces.passCondition),
            test->referenceValue,
            test->mask );
        checkResult( "::glStencilFuncSeparate" );

        ::glStencilFuncSeparate(
            GL_BACK,
            convertCondition(test->algorithmForBackFaces.passCondition),
            test->referenceValue,
            test->mask );
        checkResult( "::glStencilFuncSeparate" );
    }

    if( previousState.writeDepthValues != state.writeDepthValues ) {
        ::glDepthMask( state.writeDepthValues );
        checkResult( "::glDepthMask" );
    }
}

} // namespace

void switchOpenGlPipelineState(
    const PipelineState &previousState,
    const PipelineState &nextState )
{
    const PipelineState::Description &previousStateDescription =
        previousState.getDescription();
    const PipelineState::Description &nextStateDescription =
        nextState.getDescription();

    switchBlendingState(
        previousStateDescription.blendingState,
        nextStateDescription.blendingState );
    switchRasterizationState(
        previousStateDescription, nextStateDescription );
    switchDepthStencilState(
        previousStateDescription, nextStateDescription );
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
