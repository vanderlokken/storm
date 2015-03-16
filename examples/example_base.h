#pragma once

#include <exception>
#include <iostream>
#include <memory>

#include <storm/event_loop.h>

#ifdef _WIN32
    #include <windows.h>
#endif

class ExampleBase {
public:
    virtual ~ExampleBase() {}

    virtual void update() = 0;
    virtual void render() = 0;
};

std::unique_ptr<ExampleBase> createExample();

void exampleMain() {
    std::unique_ptr<ExampleBase> example = createExample();

    storm::EventLoop *eventLoop = storm::EventLoop::getInstance();
    eventLoop->run( [&example]() {
        example->update();
        example->render();
    });
}

#ifdef _WIN32

int CALLBACK WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
    try {
        exampleMain();
    } catch( const std::exception &error ) {
        ::MessageBoxA( 0, error.what(), "storm", MB_ICONERROR );
        return 1;
    }
    return 0;
}

#else

int main() {
    try {
        exampleMain();
    } catch( const storm::exception &error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}

#endif
