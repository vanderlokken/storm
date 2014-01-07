#pragma once

#include <storm/blending_technique.h>
#include <storm/platform/ogl/api_ogl.h>

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