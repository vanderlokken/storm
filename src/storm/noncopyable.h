#pragma once

#define NONCOPYABLE( ClassName ) \
    private: \
        ClassName( const ClassName& ); \
        ClassName& operator = ( const ClassName& );
