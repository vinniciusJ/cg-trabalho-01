#include <cmath>

#include "../graphic-primitives.h"

namespace GraphicPrimitives {

    void draw_midpoint_line(const Point p1, const Point p2, const int color, const PixelWriter& writer) {
        int x1 = p1.x;
        int y1 = p1.y;

        const int x2 = p2.x;
        const int y2 = p2.y;

        const int dx = std::abs(x2 - x1);
        const int sx = (x1 < x2) ? 1 : -1;

        const int dy = -std::abs(y2 - y1);
        const int sy = (y1 < y2) ? 1 : -1;

        int d = dx + dy;

        while (true) {
            writer(x1, y1, color);

            if (x1 == x2 && y1 == y2) {
                break;
            }

            const int d2 = 2 * d;

            if (d2 >= dy) {
                d += dy;
                x1 += sx;
            }

            if (d2 <= dx) {
                d += dx;
                y1 += sy;
            }
        }
    }

} // namespace GraphicsAlgorithms
