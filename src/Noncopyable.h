#ifndef storm_Noncopyable_h
#define storm_Noncopyable_h

#define NONCOPYABLE( ClassName ) \
    private: \
        ClassName( const ClassName& ); \
        ClassName& operator = ( const ClassName& ); \

#endif