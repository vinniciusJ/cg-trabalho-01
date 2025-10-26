#ifndef TRABALHO_01_SDL_APPLICATION_H
#define TRABALHO_01_SDL_APPLICATION_H

#pragma once

#include <SDL2/SDL.h>
#include <string>

class SdlApplication {
public:
    SdlApplication(const std::string& title, int width, int height);

    virtual ~SdlApplication();

    SdlApplication(const SdlApplication&) = delete;
    SdlApplication& operator=(const SdlApplication&) = delete;

    void run();

protected:
    virtual void on_event(const SDL_Event& event);

    virtual void on_update();

    virtual void on_render();


    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    bool running_ = false;

    int window_width_;
    int window_height_;
};

#endif //TRABALHO_01_SDL_APPLICATION_H