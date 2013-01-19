#ifndef storm_BlendingTechniqueDx9_h
#define storm_BlendingTechniqueDx9_h

#include "BlendingTechnique.h"
#include "CoreTypesDx9.h"

namespace storm {

class BlendingTechniqueDx9 : public BlendingTechnique {
public:
    BlendingTechniqueDx9( const Description& );

    virtual const Description& getDescription() const noexcept;

    D3DBLENDOP getOperation() const noexcept;
    D3DBLEND getSourceFactor() const noexcept;
    D3DBLEND getDestinationFactor() const noexcept;

private:
    static D3DBLENDOP convertOperation( Operation );
    static D3DBLEND convertFactor( Factor );

    Description _description;

    D3DBLENDOP _operation;
    D3DBLEND _sourceFactor;
    D3DBLEND _destinationFactor;
};

}

#endif