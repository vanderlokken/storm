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
    switch( semantics ) {
    case Vertex::Attribute::Semantics::Position:
        return D3DDECLUSAGE_POSITION;
    case Vertex::Attribute::Semantics::Normal:
        return D3DDECLUSAGE_NORMAL;
    case Vertex::Attribute::Semantics::Tangent:
        return D3DDECLUSAGE_TANGENT;
    case Vertex::Attribute::Semantics::Binormal:
        return D3DDECLUSAGE_BINORMAL;
    case Vertex::Attribute::Semantics::Color:
        return D3DDECLUSAGE_COLOR;
    case Vertex::Attribute::Semantics::TextureCoordinates:
        return D3DDECLUSAGE_TEXCOORD;
    case Vertex::Attribute::Semantics::BlendingWeights:
        return D3DDECLUSAGE_BLENDWEIGHT;
    case Vertex::Attribute::Semantics::BlendingIndices:
        return D3DDECLUSAGE_BLENDINDICES;
    default:
        throwInvalidArgument( "'semantics' is invalid" );
    }
}

BYTE convertAttributeFormat( Vertex::Attribute::Format format ) {
    switch( format ) {
    case Vertex::Attribute::Format::Float:
        return D3DDECLTYPE_FLOAT1;
    case Vertex::Attribute::Format::Vector2Float:
        return D3DDECLTYPE_FLOAT2;
    case Vertex::Attribute::Format::Vector3Float:
        return D3DDECLTYPE_FLOAT3;
    case Vertex::Attribute::Format::Vector4Float:
        return D3DDECLTYPE_FLOAT4;
    case Vertex::Attribute::Format::Vector4Uint8:
        return D3DDECLTYPE_UBYTE4;
    case Vertex::Attribute::Format::Vector4Uint8Normalized:
        return D3DDECLTYPE_UBYTE4N;
    case Vertex::Attribute::Format::Vector2Int16:
        return D3DDECLTYPE_SHORT2;
    case Vertex::Attribute::Format::Vector2Int16Normalized:
        return D3DDECLTYPE_SHORT2N;
    case Vertex::Attribute::Format::Vector4Int16:
        return D3DDECLTYPE_SHORT4;
    case Vertex::Attribute::Format::Vector4Int16Normalized:
        return D3DDECLTYPE_SHORT4N;
    case Vertex::Attribute::Format::Vector2Uint16Normalized:
        return D3DDECLTYPE_USHORT2N;
    case Vertex::Attribute::Format::Vector4Uint16Normalized:
        return D3DDECLTYPE_USHORT4N;
    default:
        throwInvalidArgument( "'format' is invalid" );
    }
}

bool operator < ( const Vertex::Attribute &first, const Vertex::Attribute &second ) noexcept {
    return first.semantics < second.semantics ||
        (first.semantics == second.semantics && first.format < second.format);
}

}
