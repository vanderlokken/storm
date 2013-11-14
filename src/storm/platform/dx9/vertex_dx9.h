#pragma once

#include <vector>

#include <storm/platform/win/com_pointer.h>
#include <storm/vertex.h>

struct IDirect3DVertexDeclaration9;

namespace storm {

ComPointer< IDirect3DVertexDeclaration9 > convertVertexAttributes( const std::vector<Vertex::Attribute>& );

}
