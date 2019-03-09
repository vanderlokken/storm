#pragma once

#include <functional>
#include <string>
#include <string_view>

namespace storm {

// The 'Identifier' class holds either a string of a string view. It is used
// to implement string lookup in associative containers without making
// temporary string copies.
//
// TODO: in C++20 replace with heterogeneous lookup for unordered containers.
class Identifier {
public:
    static Identifier fromString( std::string value ) {
        Identifier identifier;
        identifier._string = std::move( value );
        return identifier;
    }

    static Identifier fromStringView( std::string_view value ) {
        Identifier identifier;
        identifier._view = std::move( value );
        return identifier;
    }

    std::string_view operator * () const {
        if( _view.data() ) {
            return _view;
        }

        return _string;
    }

    bool operator == ( const Identifier &other ) const {
        return **this == *other;
    }

private:
    std::string _string;
    std::string_view _view;
};

} // namespace storm

namespace std {

template <>
class hash<storm::Identifier> {
public:
    size_t operator()( const storm::Identifier &value ) const {
        return std::hash<std::string_view>()( *value );
    }
};

} // namespace std
