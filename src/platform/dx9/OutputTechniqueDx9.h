#ifndef storm_OutputTechniqueDx9_h
#define storm_OutputTechniqueDx9_h

#include "OutputTechnique.h"

namespace storm {

class OutputTechniqueDx9 : public OutputTechnique {
public:
    OutputTechniqueDx9( const Description& ) noexcept;
    
    virtual const Description& getDescription() const noexcept;
    
private:
    Description _description;
};

}

#endif