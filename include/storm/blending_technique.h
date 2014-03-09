#pragma once

#include <memory>

namespace storm {

class BlendingTechnique {
public:
    typedef std::shared_ptr<BlendingTechnique> Pointer;

    enum class Operation {
        Addition,
        Subtraction,
        NegativeSubtraction,
        Minimum,
        Maximum
    };

    enum class Factor {
        Zero,
        One,
        SourceColor,
        InvertedSourceColor,
        DestinationColor,
        InvertedDestinationColor,
        SourceAlpha,
        InvertedSourceAlpha,
        DestinationAlpha,
        InvertedDestinationAlpha,
        SourceAlphaSaturate
    };

    struct Description {
        Operation operation;
        Factor sourceFactor;
        Factor destinationFactor;
    };

    static BlendingTechnique::Pointer create( const Description& );
    static BlendingTechnique::Pointer getDefault();

    virtual ~BlendingTechnique() { }

    virtual const Description& getDescription() const = 0;
};

}
