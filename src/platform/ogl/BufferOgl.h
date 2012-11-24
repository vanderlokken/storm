#ifndef storm_BufferOgl_h
#define storm_BufferOgl_h

#include "CoreTypesOgl.h"
#include "Noexcept.h"
#include "Noncopyable.h"
#include "ResourceType.h"

namespace storm {

class BufferOgl {
    NONCOPYABLE( BufferOgl );
public:
    BufferOgl( size_t size, const void *data, ResourceType resourceType );
    ~BufferOgl() noexcept;
    
    void getData( size_t offset, size_t size, void *data ) const;
    void setData( size_t offset, size_t size, const void *data );
    
    GLuint getHandle() const noexcept;
    
private:
    GLuint _handle;
    size_t _size;
};

}

#endif