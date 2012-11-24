#ifndef storm_ResourceTypeDx9_h
#define storm_ResourceTypeDx9_h

#include "CoreTypesDx9.h"
#include "ResourceType.h"

namespace storm {

DWORD selectResourceUsage( ResourceType );
D3DPOOL selectResourcePool( ResourceType );

}

#endif