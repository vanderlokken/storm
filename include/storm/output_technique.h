#pragma once

#include <memory>
#include <optional>

#include <storm/condition.h>

namespace storm {

class OutputTechnique {
public:
    typedef std::shared_ptr<OutputTechnique> Pointer;

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

    struct DepthTest {
        Condition passCondition;
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

    struct Description {
        std::optional<DepthTest> depthTest;
        std::optional<StencilTest> stencilTest;
        bool writeDepthValues;
    };

    static OutputTechnique::Pointer create( const Description& );
    static OutputTechnique::Pointer getDefault();
    static OutputTechnique::Pointer getDefaultWithoutDepthOutput();
    static OutputTechnique::Pointer getDefaultWithoutDepthInputOutput();

    virtual ~OutputTechnique() { }

    virtual const Description& getDescription() const = 0;
};

}
