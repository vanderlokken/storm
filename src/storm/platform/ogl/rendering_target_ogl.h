#pragma once

#include <storm/rendering_target.h>

namespace storm {

class RenderingTargetOgl : public RenderingTarget {
public:
    RenderingTargetOgl( const Description& );

    virtual const Description& getDescription() const noexcept;

private:
    Description _description;
};

}
