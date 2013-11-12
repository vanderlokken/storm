#pragma once

#include <memory>

#include "Noexcept.h"

namespace storm {

class OutputTechnique {
public:
    enum Condition {
        ConditionFalse,
        ConditionTrue,
        ConditionLess,
        ConditionLessOrEqual,
        ConditionGreater,
        ConditionGreaterOrEqual,
        ConditionEqual,
        ConditionNotEqual
    };

    enum StencilOperation {
        StencilOperationZero,
        StencilOperationKeep,
        StencilOperationReplace,
        StencilOperationIncrementTruncate,
        StencilOperationDecrementTruncate,
        StencilOperationIncrement,
        StencilOperationDecrement,
        StencilOperationInvert
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

    static std::shared_ptr<OutputTechnique> create( const Description& );
    static std::shared_ptr<OutputTechnique> getDefault();

    virtual ~OutputTechnique() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
