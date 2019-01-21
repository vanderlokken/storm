#include <iostream>
#include <exception>
#include <string>

#include <storm/display.h>

std::string formatDisplayMode( const storm::Display::Mode &mode ) {
    return
        std::to_string( mode.width ) +
        "x" +
        std::to_string( mode.height ) +
        ", " +
        std::to_string( mode.refreshRate ) + " Hz";
};

int main() {
    try {
        const std::unique_ptr<storm::Display> display =
            storm::Display::create();

        std::cerr << "Default display mode: " +
            formatDisplayMode( display->getDefaultMode() ) << std::endl;

        std::cerr << "Available display modes:" << std::endl;

        for( const storm::Display::Mode &mode : display->getSupportedModes() ) {
            std::cerr << formatDisplayMode( mode ) << std::endl;
        }
    } catch( const std::exception &error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}
