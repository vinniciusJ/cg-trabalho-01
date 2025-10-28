#include <cstddef>

#include "../graphic-primitives.h"

namespace GraphicPrimitives {
    void draw_polygon(const std::vector<Point>& vertices, const int color, const PixelWriter& writer) {
        const size_t num_vertices = vertices.size();

        if (num_vertices < 2) {
            return;
        }

        for (size_t i = 0; i < num_vertices; ++i) {
            const Point& p1 = vertices[i];

            const Point& p2 = vertices[(i + 1) % num_vertices];

            draw_midpoint_line(p1, p2, color, writer);
        }
    }
}