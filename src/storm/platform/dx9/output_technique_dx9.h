#pragma once

#include <storm/output_technique.h>

namespace storm {

class OutputTechniqueDx9 : public OutputTechnique {
public:
    OutputTechniqueDx9( const Description& ) noexcept;

    virtual const Description& getDescription() const noexcept;

private:
    Description _description;
};

}
