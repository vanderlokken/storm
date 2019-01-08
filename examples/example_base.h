#pragma once

#include <exception>
#include <iostream>
#include <memory>

#include <storm/window.h>

#ifdef _WIN32
    #include <windows.h>
#endif

class ExampleBase {
public:
    virtual ~ExampleBase() {}

    virtual void update() = 0;
    virtual void render() = 0;
};

std::unique_ptr<ExampleBase> createExample( storm::Window::Pointer window );

void exampleMain() {
    storm::Window::Pointer window = storm::Window::create();

    std::unique_ptr<ExampleBase> example = createExample( window );

    bool isRunning = true;

    const auto observer = std::make_shared<storm::WindowObserver>();
    observer->onShutdownRequested = [&] { isRunning = false; };

    window->addObserver( observer );
    window->setVisible( true );

    while( isRunning ) {
        window->processEvents();

        example->update();
        example->render();
    }
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
    } catch( const std::exception &error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}

#endif
