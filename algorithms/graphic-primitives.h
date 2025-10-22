//
// Created by vinicius.jimenez on 10/21/2025.
//

#ifndef TRABALHO_01_GRAPHIC_PRIMITIVES_H
#define TRABALHO_01_GRAPHIC_PRIMITIVES_H

#pragma once

#include <cstdint>
#include <functional>

namespace GraphicPrimitives {

    struct Point {
        int x;
        int y;
    };

    struct DoublePoint {
        double x;
        double y;
    };

    struct ClipWindow {
        int x_min, y_min;
        int x_max, y_max;
    };

    enum class RegionCode : uint8_t {
        INSIDE = 0b0000,
        LEFT   = 0b0001,
        RIGHT  = 0b0010,
        BOTTOM = 0b0100,
        TOP    = 0b1000
    };

    inline RegionCode operator|(RegionCode a, RegionCode b) {
        return static_cast<RegionCode>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }

    inline RegionCode& operator|=(RegionCode& a, RegionCode b) {
        a = a | b;
        return a;
    }

    inline RegionCode operator&(RegionCode a, RegionCode b) {
        return static_cast<RegionCode>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
    }

    inline bool operator!=(RegionCode a, RegionCode b) {
        return static_cast<uint8_t>(a) != static_cast<uint8_t>(b);
    }

    inline bool operator==(RegionCode a, RegionCode b) {
        return static_cast<uint8_t>(a) == static_cast<uint8_t>(b);
    }

    using PixelWriter = std::function<void(int, int, int)>;

    void draw_midpoint_line(Point p1, Point p2, int color, const PixelWriter& writer);

    RegionCode get_region_code(DoublePoint point, const ClipWindow& window);

    bool cohen_sutherland_clip(DoublePoint& p1, DoublePoint& p2, const ClipWindow& window);
}


#endif //TRABALHO_01_GRAPHIC_PRIMITIVES_H