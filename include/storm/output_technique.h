#pragma once

#include <memory>

#include <storm/noexcept.h>

namespace storm {

class OutputTechnique {
public:
    typedef std::shared_ptr<OutputTechnique> Pointer;

    enum class Condition {
        False,
        True,
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual,
        Equal,
        NotEqual
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

    struct DepthTest {
        bool enabled;
        Condition passCondition;
    };

    struct StencilTest {
        bool enabled;

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
          DepthTest depthTest;
        StencilTest stencilTest;
               bool writeDepthValues;
    };

    static OutputTechnique::Pointer create( const Description& );
    static OutputTechnique::Pointer getDefault();

    virtual ~OutputTechnique() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}