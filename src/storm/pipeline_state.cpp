#include <storm/pipeline_state.h>

namespace storm {

PipelineStateBuilder::PipelineStateBuilder() {
    _description.blendingState.emplace();

    _description.blendingState->colorBlending.operation =
        BlendingOperation::Addition;
    _description.blendingState->colorBlending.sourceFactor =
        BlendingFactor::SourceAlpha;
    _description.blendingState->colorBlending.targetFactor =
        BlendingFactor::InvertedSourceAlpha;

    _description.blendingState->alphaBlending =
        _description.blendingState->colorBlending;

    _description.primitiveCullMode = PrimitiveCullMode::BackFaces;
    _description.primitiveFillMode = PrimitiveFillMode::Solid;

    _description.depthTest.emplace();
    _description.depthTest->passCondition = Condition::Less;
    _description.writeDepthValues = true;
}

PipelineStateBuilder& PipelineStateBuilder::disableBlending() {
    _description.blendingState.reset();
    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::useAdditiveBlending() {
    _description.blendingState.emplace();

    _description.blendingState->colorBlending.operation =
        BlendingOperation::Addition;
    _description.blendingState->colorBlending.sourceFactor =
        BlendingFactor::SourceAlpha;
    _description.blendingState->colorBlending.targetFactor =
        BlendingFactor::One;

    _description.blendingState->alphaBlending =
        _description.blendingState->colorBlending;

    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::disableCulling() {
    _description.primitiveCullMode = PrimitiveCullMode::Nothing;
    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::disableDepthClipping() {
    _description.depthClippingEnabled = false;
    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::enableRectangleClipping() {
    _description.rectangleClippingEnabled = true;
    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::disableDepthOutput() {
    _description.writeDepthValues = false;
    return *this;
}

PipelineStateBuilder& PipelineStateBuilder::disableDepthTest() {
    _description.depthTest.reset();
    return *this;
}

PipelineState::Pointer PipelineStateBuilder::build() const {
    return PipelineState::create( _description );
}

const PipelineState::Description&
PipelineStateBuilder::getStateDescription() const {
    return _description;
}

}
