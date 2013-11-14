#pragma once

#include <storm/platform/dx9/core_types_dx9.h>
#include <storm/resource_type.h>

namespace storm {

DWORD selectResourceUsage( ResourceType );
D3DPOOL selectResourcePool( ResourceType );

}
