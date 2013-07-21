#ifndef storm_BlendingTechnique_h
#define storm_BlendingTechnique_h

#include <memory>

#include "Noexcept.h"

namespace storm {

class BlendingTechnique {
public:
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

    static std::shared_ptr<BlendingTechnique> create( const Description& );
    static std::shared_ptr<BlendingTechnique> getDefault();

    virtual ~BlendingTechnique() { }

    virtual const Description& getDescription() const noexcept = 0;
};

}

#endif