#ifndef storm_BlendingTechniqueOgl_h
#define storm_BlendingTechniqueOgl_h

#include "BlendingTechnique.h"
#include "CoreTypesOgl.h"

namespace storm {

class BlendingTechniqueOgl : public BlendingTechnique {
public:
    BlendingTechniqueOgl( const Description& );

    virtual const Description& getDescription() const noexcept;

    GLenum getOperation() const noexcept;
    GLenum getSourceFactor() const noexcept;
    GLenum getDestinationFactor() const noexcept;

private:
    static GLenum convertOperation( Operation );
    static GLenum convertFactor( Factor );

    Description _description;
    GLenum _operation;
    GLenum _sourceFactor;
    GLenum _destinationFactor;
};

}

#endif