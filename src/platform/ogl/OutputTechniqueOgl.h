#ifndef storm_OutputTechniqueOgl_h
#define storm_OutputTechniqueOgl_h

#include "OutputTechnique.h"

namespace storm {

class OutputTechniqueOgl : public OutputTechnique {
public:
    OutputTechniqueOgl( const Description& );

    virtual const Description& getDescription() const noexcept;

private:
    Description _description;
};

}

#endif
