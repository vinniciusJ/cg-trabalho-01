#include "demo.h"

int main(int argc, char* argv[]) {
    try {
        GraphicPrimitivesDemo demo;

        demo.run();
    }
    catch (const std::exception& e) {
        SDL_Log("Fatal Error: %s", e.what());

        return 1;
    }

    return 0;
}