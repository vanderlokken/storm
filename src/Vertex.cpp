#include "Vertex.h"

#include "Exception.h"

namespace storm {

unsigned short Vertex::Attribute::getSize() const {
    unsigned short result;
    
    switch( format ) {
    case FormatFloat:
    case Format4Uint8:
    case Format4Uint8Normalized:
    case Format2Int16:
    case Format2Int16Normalized:
    case Format2Uint16Normalized:
        result = 4;
        break;
    
    case Format2Float:
    case Format4Int16:
    case Format4Int16Normalized:
    case Format4Uint16Normalized:
        result = 8;
        break;
        
    case Format3Float:
        result = 12;
        break;
        
    case Format4Float:
        result = 16;
        break;
        
    default:
        throwRuntimeError( "'format' is invalid" );
    }
    return result;
}

}