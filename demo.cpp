#include <vector>
#include <utility>
#include <cmath>
#include <functional>

#include "graphic-primitives/graphic-primitives.h"

#include "demo.h"

void GraphicPrimitivesDemo::on_render() {

    using namespace GraphicPrimitives;

    auto sdl_pixel_writer = [this](const int x, const int y, const int color) {
        const Uint8 r = (color >> 16) & 0xFF;
        const Uint8 g = (color >> 8)  & 0xFF;
        const Uint8 b = (color)       & 0xFF;
        constexpr Uint8 a = 0xFF;

        SDL_SetRenderDrawColor(renderer_, r, g, b, a);
        SDL_RenderDrawPoint(renderer_, x, y);
    };

    constexpr int BLACK       = 0x000000;
    constexpr int BLUE_SKY    = 0x87CEEB;
    constexpr int GREEN_GRASS = 0x228B22;
    constexpr int ORANGE_SUN  = 0xFF8C00;
    constexpr int BROWN_ROOF  = 0x8B4513;
    constexpr int LIGHT_YELLOW_HOUSE = 0xFFFDD0;
    constexpr int GRAY_WINDOW = 0x808080;
    constexpr int CLIP_COLOR = 0xFF0000;

    const std::vector<Point> sky_rect = {
        {0, 0}, {WINDOW_WIDTH, 0}, {WINDOW_WIDTH, 450}, {0, 450}
    };

    fill_polygon_scanline(sky_rect, BLUE_SKY, sdl_pixel_writer);

    const std::vector<Point> grass_rect = {
        {0, 450}, {WINDOW_WIDTH, 450}, {WINDOW_WIDTH, WINDOW_HEIGHT}, {0, WINDOW_HEIGHT}
    };

    fill_polygon_scanline(grass_rect, GREEN_GRASS, sdl_pixel_writer);

    std::vector<Point> sun_vertices;

    constexpr int sun_radius = 40;
    constexpr int sun_center_x = 700;
    constexpr int sun_center_y = 100;
    constexpr int sun_segments = 20;

    for (int i = 0; i < sun_segments; ++i) {
        const double angle = 2.0 * M_PI * static_cast<double>(i) / sun_segments;

        sun_vertices.push_back({
            static_cast<int>(sun_center_x + sun_radius * cos(angle)),
            static_cast<int>(sun_center_y + sun_radius * sin(angle))
        });
    }

    fill_polygon_scanline(sun_vertices, ORANGE_SUN, sdl_pixel_writer);

    const std::vector<Point> house_base = {
        {200, 250}, {600, 250}, {600, 450}, {200, 450}
    };

    fill_polygon_scanline(house_base, LIGHT_YELLOW_HOUSE, sdl_pixel_writer); // <-- Usando a nova cor aqui
    draw_polygon(house_base, BLACK, sdl_pixel_writer); // Contorno

    const std::vector<Point> roof_triangle = {
        {180, 250}, {620, 250}, {400, 150}
    };

    fill_polygon_scanline(roof_triangle, BROWN_ROOF, sdl_pixel_writer);
    draw_polygon(roof_triangle, BLACK, sdl_pixel_writer); // Contorno

    const std::vector<Point> door_rect = {
        {250, 350}, {300, 350}, {300, 450}, {250, 450}
    };

    fill_polygon_scanline(door_rect, BROWN_ROOF, sdl_pixel_writer);
    draw_polygon(door_rect, BLACK, sdl_pixel_writer); // Contorno

    constexpr ClipWindow window_frame = {350, 300, 550, 400};

    draw_midpoint_line({window_frame.x_min, window_frame.y_min}, {window_frame.x_max, window_frame.y_min}, CLIP_COLOR, sdl_pixel_writer);
    draw_midpoint_line({window_frame.x_max, window_frame.y_min}, {window_frame.x_max, window_frame.y_max}, CLIP_COLOR, sdl_pixel_writer);
    draw_midpoint_line({window_frame.x_max, window_frame.y_max}, {window_frame.x_min, window_frame.y_max}, CLIP_COLOR, sdl_pixel_writer);
    draw_midpoint_line({window_frame.x_min, window_frame.y_max}, {window_frame.x_min, window_frame.y_min}, CLIP_COLOR, sdl_pixel_writer);

    DoublePoint h_p1 = {340, 350}; // Começa fora (esquerda)
    DoublePoint h_p2 = {560, 350}; // Termina fora (direita)

    DoublePoint v_p1 = {450, 290}; // Começa fora (topo)
    DoublePoint v_p2 = {450, 410}; // Termina fora (base)

    if (cohen_sutherland_clip(h_p1, h_p2, window_frame)) {
        draw_midpoint_line(
            {static_cast<int>(std::round(h_p1.x)), static_cast<int>(std::round(h_p1.y))},
            {static_cast<int>(std::round(h_p2.x)), static_cast<int>(std::round(h_p2.y))},
            GRAY_WINDOW, sdl_pixel_writer);
    }

    if (cohen_sutherland_clip(v_p1, v_p2, window_frame)) {
        draw_midpoint_line(
            {static_cast<int>(std::round(v_p1.x)), static_cast<int>(std::round(v_p1.y))},
            {static_cast<int>(std::round(v_p2.x)), static_cast<int>(std::round(v_p2.y))},
            GRAY_WINDOW, sdl_pixel_writer);
    }
}