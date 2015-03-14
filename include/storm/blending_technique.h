#pragma once

#include <memory>

namespace storm {

class BlendingTechnique {
public:
    typedef std::shared_ptr<BlendingTechnique> Pointer;

    enum class Operation {
        // sourceColor * sourceFactor + destinationColor * destinationFactor
        Addition,
        // sourceColor * sourceFactor - destinationColor * destinationFactor
        Subtraction,
        // destinationColor * destinationFactor - sourceColor * sourceFactor
        NegativeSubtraction,
        // min( sourceColor, destinationColor )
        Minimum,
        // max( sourceColor, destinationColor )
        Maximum
    };

    enum class Factor {
        // (0, 0, 0, 0)
        Zero,
        // (1, 1, 1, 1)
        One,
        // (sourceR, sourceG, sourceB, sourceA)
        SourceColor,
        // (1 - sourceR, 1 - sourceG, 1 - sourceB, 1 - sourceA)
        InvertedSourceColor,
        // (destinationR, destinationG, destinationB, destinationA)
        DestinationColor,
        // (1 - destinationR, 1 - destinationG, 1 - destinationB, 1 - destinationA)
        InvertedDestinationColor,
        // (sourceA, sourceA, sourceA, sourceA)
        SourceAlpha,
        // (1 - sourceA, 1 - sourceA, 1 - sourceA, 1 - sourceA)
        InvertedSourceAlpha,
        // (destinationA, destinationA, destinationA, destinationA)
        DestinationAlpha,
        // (1 - destinationA, 1 - destinationA, 1 - destinationA, 1 - destinationA)
        InvertedDestinationAlpha,
        // (
        //     min(sourceAlpha, (1 - destinationA)),
        //     min(sourceAlpha, (1 - destinationA)),
        //     min(sourceAlpha, (1 - destinationA)),
        //     1
        // )
        SourceAlphaSaturate
    };

    struct Equation {
        Operation operation;
        Factor sourceFactor;
        Factor destinationFactor;
    };

    struct Description {
        // Equation for (sourceR, sourceG, sourceB, 0) and
        // (destinationR, destinationG, destinationB, 0)
        Equation colorEquation;
        // Equation for (0, 0, 0, sourceA) and (0, 0, 0, destinationA)
        Equation alphaEquation;
    };

    static BlendingTechnique::Pointer create( const Description& );
    static BlendingTechnique::Pointer getDefault();

    virtual ~BlendingTechnique() { }

    virtual const Description& getDescription() const = 0;
};

}
