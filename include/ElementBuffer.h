#ifndef storm_ElementBuffer_h
#define storm_ElementBuffer_h

#include <memory>

#include "Noexcept.h"

namespace storm {

class IndexBuffer;
class VertexBuffer;

class ElementBuffer {
public:
    enum ElementTopology {
        ElementTopologyList,
        ElementTopologyStrip
    };
    
    struct Description {
        ElementTopology elementTopology;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
    
    static std::shared_ptr<ElementBuffer> create( const Description& );
    
    virtual ~ElementBuffer() noexcept { }
    
    virtual const Description& getDescription() const noexcept = 0;
};

}

#endif