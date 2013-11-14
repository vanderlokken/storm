#include <storm/platform/dx9/vertex_dx9.h>

#include <map>

#include <d3d9.h>

#include <storm/platform/dx9/rendering_system_dx9.h>
#include <storm/platform/win/check_result.h>

namespace storm {

ComPointer< IDirect3DVertexDeclaration9 > convert( const std::vector<Vertex::Attribute>& );

BYTE convertAttributeSemantics( Vertex::Attribute::Semantics );
BYTE convertAttributeFormat( Vertex::Attribute::Format );

bool operator < ( const Vertex::Attribute&, const Vertex::Attribute& ) noexcept;

ComPointer< IDirect3DVertexDeclaration9 > convertVertexAttributes(
    const std::vector<Vertex::Attribute> &attributes )
{
    // The following map specialization implicitly uses the ordering relationship operator, declared above
    static std::map< std::vector< Vertex::Attribute >, ComPointer< IDirect3DVertexDeclaration9 > > declarations;

    auto result = declarations.find( attributes );

    if( result == declarations.end() )
        result = declarations.insert( std::make_pair(attributes, convert(attributes)) ).first;
    return result->second;
}

ComPointer< IDirect3DVertexDeclaration9 > convert(
    const std::vector<Vertex::Attribute> &attributes )
{
    // The number of the vertex declaration elements is equal to the number
    // of the vertex attributes + 1 D3DDECL_END element.
    std::vector< D3DVERTEXELEMENT9 > declarationElements( attributes.size() + 1 );

    auto element = declarationElements.begin();
    auto attribute = attributes.cbegin();

    WORD previousAttributeOffset = 0;
    WORD previousAttributeSize = 0;

    std::map< BYTE, BYTE > usageCounters;

    while( attribute != attributes.cend() ) {

        element->Stream     = 0;
        element->Offset     = previousAttributeOffset + previousAttributeSize;
        element->Type       = convertAttributeFormat( attribute->format );
        element->Method     = D3DDECLMETHOD_DEFAULT;
        element->Usage      = convertAttributeSemantics( attribute->semantics );
        element->UsageIndex = usageCounters[ element->Usage ]++;

        previousAttributeOffset = element->Offset;
        previousAttributeSize = attribute->getSize();

        ++element;
        ++attribute;
    }

    const D3DVERTEXELEMENT9 closingElement = D3DDECL_END();
    declarationElements.back() = closingElement;

    ComPointer< IDirect3DDevice9 > device = RenderingSystemDx9::getDevice();
    ComPointer< IDirect3DVertexDeclaration9 > vertexDeclaration;

    const HRESULT result = device->CreateVertexDeclaration( declarationElements.data(), vertexDeclaration.getAddress() );
    checkResult( result, "IDirect3DDevice9::CreateVertexDeclaration" );

    return vertexDeclaration;
}

BYTE convertAttributeSemantics( Vertex::Attribute::Semantics semantics ) {
    BYTE result;

    switch( semantics ) {
    case Vertex::Attribute::SemanticsPosition:
        result = D3DDECLUSAGE_POSITION;
        break;

    case Vertex::Attribute::SemanticsNormal:
        result = D3DDECLUSAGE_NORMAL;
        break;

    case Vertex::Attribute::SemanticsTangent:
        result = D3DDECLUSAGE_TANGENT;
        break;

    case Vertex::Attribute::SemanticsBinormal:
        result = D3DDECLUSAGE_BINORMAL;
        break;

    case Vertex::Attribute::SemanticsColor:
        result = D3DDECLUSAGE_COLOR;
        break;

    case Vertex::Attribute::SemanticsTextureCoordinates:
        result = D3DDECLUSAGE_TEXCOORD;
        break;

    case Vertex::Attribute::SemanticsBlendingWeights:
        result = D3DDECLUSAGE_BLENDWEIGHT;
        break;

    case Vertex::Attribute::SemanticsBlendingIndices:
        result = D3DDECLUSAGE_BLENDINDICES;
        break;

    default:
        throwInvalidArgument( "'semantics' is invalid" );
    }
    return result;
}

BYTE convertAttributeFormat( Vertex::Attribute::Format format ) {
    BYTE result;

    switch( format ) {
    case Vertex::Attribute::FormatFloat:
        result = D3DDECLTYPE_FLOAT1;
        break;

    case Vertex::Attribute::Format2Float:
        result = D3DDECLTYPE_FLOAT2;
        break;

    case Vertex::Attribute::Format3Float:
        result = D3DDECLTYPE_FLOAT3;
        break;

    case Vertex::Attribute::Format4Float:
        result = D3DDECLTYPE_FLOAT4;
        break;

    case Vertex::Attribute::Format4Uint8:
        result = D3DDECLTYPE_UBYTE4;
        break;

    case Vertex::Attribute::Format4Uint8Normalized:
        result = D3DDECLTYPE_UBYTE4N;
        break;

    case Vertex::Attribute::Format2Int16:
        result = D3DDECLTYPE_SHORT2;
        break;

    case Vertex::Attribute::Format2Int16Normalized:
        result = D3DDECLTYPE_SHORT2N;
        break;

    case Vertex::Attribute::Format4Int16:
        result = D3DDECLTYPE_SHORT4;
        break;

    case Vertex::Attribute::Format4Int16Normalized:
        result = D3DDECLTYPE_SHORT4N;
        break;

    case Vertex::Attribute::Format2Uint16Normalized:
        result = D3DDECLTYPE_USHORT2N;
        break;

    case Vertex::Attribute::Format4Uint16Normalized:
        result = D3DDECLTYPE_USHORT4N;
        break;

    default:
        throwInvalidArgument( "'format' is invalid" );
    }
    return result;
}

bool operator < ( const Vertex::Attribute &first, const Vertex::Attribute &second ) noexcept {
    return first.semantics < second.semantics ||
        (first.semantics == second.semantics && first.format < second.format);
}

}