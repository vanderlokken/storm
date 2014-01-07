#pragma once

#define NONCOPYABLE( ClassName ) \
    private: \
        ClassName( const ClassName& ) = delete; \
        ClassName& operator = ( const ClassName& ) = delete;
