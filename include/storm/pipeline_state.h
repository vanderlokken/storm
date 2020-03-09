#pragma once

#include <memory>
#include <optional>

#include <storm/condition.h>

namespace storm {

// BlendingOperation   │ Color                       | Alpha
// ────────────────────┼─────────────────────────────┼─────────────────────────
// Addition            │ source.rgb * factorS +      │ source.a * factorS +
//                     │ target.rgb * factorT        │ target.a * factorT
//                     │                             │
// Subtraction         │ source.rgb * factorS -      │ source.a * factorS -
//                     │ target.rgb * factorT        │ target.a * factorT
//                     │                             │
// NegativeSubtraction │ target.rgb * factorT -      │ target.a * factorT -
//                     │ source.rgb * factorS        │ source.a * factorS
//                     │                             │
// Minimum             │ min(source.rgb, target.rgb) │ min(source.a, target.a)
//                     │                             │
// Maximum             │ max(source.rgb, target.rgb) │ max(source.a, target.a)
//                     │                             │

// BlendingFactor      │ Color                             │ Alpha
// ────────────────────┼───────────────────────────────────┼───────────────────
// Zero                │ vec3(0)                           │ 0
// One                 │ vec3(1)                           │ 1
// SourceColor         │ source.rgb                        │ source.a
// InvertedSourceColor │ 1 - source.rgb                    │ 1 - source.a
// TargetColor         │ target.rgb                        │ target.a
// InvertedTargetColor │ 1 - target.rgb                    │ 1 - target.a
// SourceAlpha         │ vec3(source.a)                    │ source.a
// InvertedSourceAlpha │ 1 - vec3(source.a)                │ 1 - source.a
// TargetAlpha         │ vec3(target.a)                    │ target.a
// InvertedTargetAlpha │ 1 - vec3(target.a)                │ 1 - target.a
// SourceAlphaSaturate │ vec3(min(source.a, 1 - target.a)) │ 1

enum class BlendingOperation {
    Addition,
    Subtraction,
    NegativeSubtraction,
    Minimum,
    Maximum
};

enum class BlendingFactor {
    Zero,
    One,
    SourceColor,
    InvertedSourceColor,
    TargetColor,
    InvertedTargetColor,
    SourceAlpha,
    InvertedSourceAlpha,
    TargetAlpha,
    InvertedTargetAlpha,
    SourceAlphaSaturate
};

struct BlendingState {
    struct Algorithm {
        BlendingOperation operation;
        BlendingFactor sourceFactor;
        BlendingFactor targetFactor;
    };

    Algorithm colorBlending;
    Algorithm alphaBlending;
};

enum class PrimitiveCullMode {
    Nothing,
    FrontFaces,
    BackFaces
};

enum class PrimitiveFillMode {
    Solid,
    Wireframe
};

struct DepthTest {
    Condition passCondition;
};

enum class StencilOperation {
    Zero,
    Keep,
    Replace,
    IncrementTruncate,
    DecrementTruncate,
    Increment,
    Decrement,
    Invert
};

struct StencilTest {
    unsigned int referenceValue;
    unsigned int mask;

    struct Algorithm {
        Condition passCondition;
        StencilOperation operationOnStencilTestFail;
        StencilOperation operationOnDepthTestFail;
        StencilOperation operationOnDepthTestPass;
    };

    Algorithm algorithmForFrontFaces;
    Algorithm algorithmForBackFaces;
};

class PipelineState {
public:
    using Pointer = std::shared_ptr<PipelineState>;

    struct Description {
        std::optional<BlendingState> blendingState;

        PrimitiveCullMode primitiveCullMode;
        PrimitiveFillMode primitiveFillMode;

        bool rectangleClippingEnabled;
        bool depthClippingEnabled;

        int depthBiasConstantFactor;
        float depthBiasSlopeFactor;

        size_t clippingDistanceArraySize;

        std::optional<DepthTest> depthTest;
        std::optional<StencilTest> stencilTest;
        bool writeDepthValues;
    };

    static Pointer create( const Description& );

    virtual ~PipelineState() = default;

    virtual const Description& getDescription() const = 0;
};

class PipelineStateBuilder {
public:
    PipelineStateBuilder();

    PipelineStateBuilder& disableBlending();
    PipelineStateBuilder& useAdditiveBlending();

    PipelineStateBuilder& disableCulling();
    PipelineStateBuilder& disableDepthClipping();

    PipelineStateBuilder& enableRectangleClipping();

    PipelineStateBuilder& disableDepthOutput();
    PipelineStateBuilder& disableDepthTest();

    PipelineState::Pointer build() const;

    const PipelineState::Description& getStateDescription() const;

private:
    PipelineState::Description _description = {};
};

}
