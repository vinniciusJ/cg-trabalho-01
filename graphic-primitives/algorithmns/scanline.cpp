#include <cmath>

#include "../graphic-primitives.h"

namespace GraphicPrimitives {
    void fill_polygon_scanline(const std::vector<Point>& vertices, const int color, const PixelWriter& writer) {
        if (vertices.empty()) {
            return;
        }
        auto y_comp = [](const Point& a, const Point& b) { return a.y < b.y; };

        const int min_y = std::min_element(vertices.begin(), vertices.end(), y_comp)->y;
        const int max_y = std::max_element(vertices.begin(), vertices.end(), y_comp)->y;

        const size_t num_vertices = vertices.size();

        for (int y = min_y; y <= max_y; ++y) {
            std::vector<int> intersections;

            for (size_t i = 0; i < num_vertices; ++i) {
                Point p1 = vertices[i];
                Point p2 = vertices[(i + 1) % num_vertices];

                if (p1.y > p2.y) {
                    std::swap(p1, p2);
                }

                if (y > p1.y && y <= p2.y) {
                    if (p2.y - p1.y != 0) {
                        double x_intersection = p1.x + (static_cast<double>(y - p1.y) * (p2.x - p1.x))
                                                     / (p2.y - p1.y);

                        intersections.push_back(static_cast<int>(std::round(x_intersection)));
                    }
                }
            }

            std::sort(intersections.begin(), intersections.end());

            for (size_t i = 0; i < intersections.size(); i += 2) {
                if (i + 1 < intersections.size()) {
                    const int x_start = intersections[i];
                    const int x_end = intersections[i + 1];

                    if (x_start < x_end) {
                       draw_midpoint_line({x_start, y}, {x_end, y}, color, writer);
                    }
                }
            }
        }
    }
}