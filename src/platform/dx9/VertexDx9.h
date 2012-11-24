#ifndef storm_VertexDx9_h
#define storm_VertexDx9_h

#include <vector>

#include "platform/win/ComPointer.h"
#include "Vertex.h"

struct IDirect3DVertexDeclaration9;

namespace storm {

ComPointer< IDirect3DVertexDeclaration9 > convertVertexAttributes( const std::vector<Vertex::Attribute>& );

}

#endif