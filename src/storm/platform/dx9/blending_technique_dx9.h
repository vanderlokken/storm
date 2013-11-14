#pragma once

#include <storm/blending_technique.h>
#include <storm/platform/dx9/core_types_dx9.h>

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
