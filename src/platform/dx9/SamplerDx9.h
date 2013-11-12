#pragma once

#include "CoreTypesDx9.h"
#include "Sampler.h"

namespace storm {

class SamplerDx9 : public Sampler {
public:
    SamplerDx9( const Description& );

    virtual const Description& getDescription() const noexcept;

private:
    static D3DTEXTUREFILTERTYPE selectMinifyingFilter( const Description& );
    static D3DTEXTUREFILTERTYPE selectMagnifyingFilter( const Description& );
    static D3DTEXTUREFILTERTYPE selectMipmappingFilter( const Description& );

    static D3DTEXTUREADDRESS convertWrapMode( WrapMode );

    Description _description;
    D3DTEXTUREFILTERTYPE _minifyingFilter;
    D3DTEXTUREFILTERTYPE _magnifyingFilter;
    D3DTEXTUREFILTERTYPE _mipmappingFilter;
    std::array<D3DTEXTUREADDRESS, 3> _wrapModes;
    D3DCOLOR _borderColor;
};

}
