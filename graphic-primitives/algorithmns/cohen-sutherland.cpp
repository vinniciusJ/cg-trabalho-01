#include "../graphic-primitives.h"

namespace GraphicPrimitives {
    RegionCode get_region_code(const DoublePoint point, const ClipWindow& window) {
        auto code = RegionCode::INSIDE;

        if (point.x < window.x_min)
            code |= RegionCode::LEFT;
        else if (point.x > window.x_max)
            code |= RegionCode::RIGHT;

        if (point.y < window.y_min)
            code |= RegionCode::BOTTOM;
        else if (point.y > window.y_max)
            code |= RegionCode::TOP;

        return code;
    }

    bool cohen_sutherland_clip(DoublePoint& p1, DoublePoint& p2, const ClipWindow& window) {
        RegionCode code1 = get_region_code(p1, window);
        RegionCode code2 = get_region_code(p2, window);

        bool accepted = false;

        while (true) {
            if (code1 == RegionCode::INSIDE && code2 == RegionCode::INSIDE) {
                accepted = true;

                break;
            }

            if ((code1 & code2) != RegionCode::INSIDE) {
                break;
            }

            DoublePoint new_point = {0.0, 0.0};

            const RegionCode outside_code = (code1 != RegionCode::INSIDE) ? code1 : code2;

            if ((outside_code & RegionCode::TOP) != RegionCode::INSIDE) {
                new_point.x = p1.x + (p2.x - p1.x) * (window.y_max - p1.y) / (p2.y - p1.y);
                new_point.y = window.y_max;
            } else if ((outside_code & RegionCode::BOTTOM) != RegionCode::INSIDE) {
                new_point.x = p1.x + (p2.x - p1.x) * (window.y_min - p1.y) / (p2.y - p1.y);
                new_point.y = window.y_min;
            } else if ((outside_code & RegionCode::RIGHT) != RegionCode::INSIDE) {
                new_point.y = p1.y + (p2.y - p1.y) * (window.x_max - p1.x) / (p2.x - p1.x);
                new_point.x = window.x_max;
            } else if ((outside_code & RegionCode::LEFT) != RegionCode::INSIDE) {
                new_point.y = p1.y + (p2.y - p1.y) * (window.x_min - p1.x) / (p2.x - p1.x);
                new_point.x = window.x_min;
            }

            if (outside_code == code1) {
                p1 = new_point;
                code1 = get_region_code(p1, window);
            } else {
                p2 = new_point;
                code2 = get_region_code(p2, window);
            }
        }

        return accepted;
    }
}