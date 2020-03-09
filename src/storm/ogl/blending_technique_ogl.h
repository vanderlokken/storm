#pragma once

#include <storm/blending_technique.h>
#include <storm/ogl/api_ogl.h>

namespace storm {

class BlendingTechniqueOgl : public BlendingTechnique {
public:
    struct EquationOgl {
        GLenum operation;
        GLenum sourceFactor;
        GLenum destinationFactor;
    };

    BlendingTechniqueOgl( const Description& );

    const Description& getDescription() const override;

    EquationOgl getColorEquation() const;
    EquationOgl getAlphaEquation() const;

private:
    static GLenum convertOperation( Operation );
    static GLenum convertFactor( Factor );

    Description _description;
    EquationOgl _colorEquation;
    EquationOgl _alphaEquation;
};

}
