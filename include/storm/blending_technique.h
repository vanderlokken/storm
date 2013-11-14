#pragma once

#include <memory>

#include <storm/noexcept.h>

namespace storm {

class BlendingTechnique {
public:
    typedef std::shared_ptr<BlendingTechnique> Pointer;

    enum Operation {
        OperationAddition,
        OperationSubtraction,
        OperationNegativeSubtraction,
        OperationMinimum,
        OperationMaximum
    };

    enum Factor {
        FactorZero,
        FactorOne,
        FactorSourceColor,
        FactorInvertedSourceColor,
        FactorDestinationColor,
        FactorInvertedDestinationColor,
        FactorSourceAlpha,
        FactorInvertedSourceAlpha,
        FactorDestinationAlpha,
        FactorInvertedDestinationAlpha,
        FactorSourceAlphaSaturate
    };

    struct Description {
        Operation operation;
        Factor sourceFactor;
        Factor destinationFactor;
    };

    static BlendingTechnique::Pointer create( const Description& );
    static BlendingTechnique::Pointer getDefault();

    virtual ~BlendingTechnique() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}
