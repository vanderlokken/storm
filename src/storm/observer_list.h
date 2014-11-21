#pragma once

#include <algorithm>
#include <list>

namespace storm {

template<class Observer>
class ObserverList {
public:
    // The 'ObserverList' class allows to add or remove elements during the
    // iteration process.

    ObserverList() : _compressed( true ) {}

    void add( const Observer *observer ) {
        const bool existing = std::find(
            _observers.begin(),
            _observers.end(),
            observer ) != _observers.end();

        if( !existing )
            _observers.push_back( observer );
    }

    void remove( const Observer *observer ) {
        const auto iterator = std::find(
            _observers.begin(),
            _observers.end(),
            observer );

        if( iterator != _observers.end() ) {
            *iterator = nullptr;
            _compressed = false;
        }
    }

    template<class ObserverCallback, class... Args>
    void notify(ObserverCallback observerCallback, const Args&... args) {
        for( const Observer *observer : _observers )
            if( observer && observer->*observerCallback )
                (observer->*observerCallback)( args... );
        compress();
    }

    template<class Callback>
    void forEach( const Callback &callback ) {
        for( const Observer *observer : _observers )
            if( observer )
                callback( *observer );
        compress();
    }

private:
    void compress() {
        if( !_compressed ) {
            _observers.remove( nullptr );
            _compressed = true;
        }
    }

    std::list<const Observer*> _observers;
    bool _compressed;
};

}
