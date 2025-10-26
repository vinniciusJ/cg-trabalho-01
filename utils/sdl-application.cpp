#include "sdl-application.h"
#include <stdexcept>

SdlApplication::SdlApplication(const std::string& title, const int width, const int height)
    : window_width_(width), window_height_(height) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Unable to initialize SDL: ") + SDL_GetError());
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width_,
        window_height_,
        SDL_WINDOW_SHOWN
    );

    if (window_ == nullptr) {
        SDL_Quit();
        throw std::runtime_error(std::string("Could not create window: ") + SDL_GetError());
    }

    renderer_ = SDL_CreateRenderer(
        window_,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer_ == nullptr) {
        SDL_DestroyWindow(window_);
        SDL_Quit();
        throw std::runtime_error(std::string("Could not create renderer: ") + SDL_GetError());
    }

    running_ = true;

    SDL_Log("SdlApplication initialized successfully.");
}

SdlApplication::~SdlApplication() {
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_) {
        SDL_DestroyWindow(window_);
    }

    SDL_Quit();
    SDL_Log("SdlApplication cleaned up.");
}

void SdlApplication::run() {
    SDL_Event event;

    while (running_) {
        while (SDL_PollEvent(&event)) {
            on_event(event);
        }

        on_update();

        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);

        on_render();

        SDL_RenderPresent(renderer_);
    }
}

void SdlApplication::on_event(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        running_ = false;
    }
}

void SdlApplication::on_update() {
}

void SdlApplication::on_render() {

}
