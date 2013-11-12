#pragma once

#include "CoreTypesDx9.h"
#include "ResourceType.h"

namespace storm {

DWORD selectResourceUsage( ResourceType );
D3DPOOL selectResourcePool( ResourceType );

}
