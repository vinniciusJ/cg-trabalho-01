#include <SDL2/SDL.h>


#include <vector>
#include <utility>
#include <cmath>

#include "algorithms/graphic-primitives.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Cohen-Sutherland Clipping Example",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == nullptr) {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    auto sdl_pixel_writer = [renderer](int x, int y, int color) {
        const Uint8 r = (color >> 16) & 0xFF;
        const Uint8 g = (color >> 8)  & 0xFF;
        const Uint8 b = (color)       & 0xFF;
        const Uint8 a = 0xFF;

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderDrawPoint(renderer, x, y);
    };

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        using namespace GraphicPrimitives;

        const int RED = 0xFF0000;
        const int GREEN = 0x00FF00;
        const int BLUE = 0x0000FF;
        const int WHITE = 0xFFFFFF;
        const int YELLOW = 0xFFFF00;
        const int GRAY = 0x808080;


        constexpr ClipWindow clip_window = {200, 150, 600, 450};

        std::vector<std::pair<DoublePoint, DoublePoint>> test_lines = {
            // Caso 1: Trivialmente Aceita (totalmente dentro)
            {{300, 200}, {500, 300}},
            // Caso 2: Trivialmente Rejeitada (totalmente fora, topo-esquerda)
            {{10, 10}, {100, 100}},
            // Caso 3: Trivialmente Rejeitada (totalmente fora, baixo-direita)
            {{700, 500}, {750, 550}},
            // Caso 4: Recorte (de dentro para a direita)
            {{400, 300}, {700, 350}},
            // Caso 5: Recorte (da esquerda para dentro)
            {{100, 300}, {500, 300}},
            // Caso 6: Recorte (cruzando topo e esquerda)
            {{150, 100}, {250, 200}},
            // Caso 7: Recorte (cruzando topo e direita)
            {{500, 100}, {700, 400}},
            // Caso 8: Recorte (linha longa cruzando duas bordas)
            {{100, 100}, {700, 500}}
        };

        draw_midpoint_line({clip_window.x_min, clip_window.y_min}, {clip_window.x_max, clip_window.y_min}, YELLOW, sdl_pixel_writer);
        draw_midpoint_line({clip_window.x_max, clip_window.y_min}, {clip_window.x_max, clip_window.y_max}, YELLOW, sdl_pixel_writer);
        draw_midpoint_line({clip_window.x_max, clip_window.y_max}, {clip_window.x_min, clip_window.y_max}, YELLOW, sdl_pixel_writer);
        draw_midpoint_line({clip_window.x_min, clip_window.y_max}, {clip_window.x_min, clip_window.y_min}, YELLOW, sdl_pixel_writer);

        for (const auto&[fst, snd] : test_lines) {
            const Point p1 = {static_cast<int>(std::round(fst.x)), static_cast<int>(std::round(fst.y))};
            const Point p2 = {static_cast<int>(std::round(snd.x)), static_cast<int>(std::round(snd.y))};

            draw_midpoint_line(p1, p2, GRAY, sdl_pixel_writer);
        }

        for (auto [fst, snd] : test_lines) {

            if (cohen_sutherland_clip(fst, snd, clip_window)) {
                const Point p1_clipped = {static_cast<int>(std::round(fst.x)), static_cast<int>(std::round(fst.y))};
                const Point p2_clipped = {static_cast<int>(std::round(snd.x)), static_cast<int>(std::round(snd.y))};

                draw_midpoint_line(p1_clipped, p2_clipped, GREEN, sdl_pixel_writer);
            }
        }

        std::vector<Point> boundary_box = {
            {10, 10},
            {790, 10},
            {790, 590},
            {10, 590}
        };

        draw_polygon(boundary_box, YELLOW, sdl_pixel_writer);

        std::vector<Point> pentagon = {
            {400, 150},
            {550, 250},
            {500, 450},
            {300, 450},
            {250, 250}
        };

        draw_polygon(pentagon, GREEN, sdl_pixel_writer);

        fill_polygon_scanline(pentagon, GREEN, sdl_pixel_writer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}