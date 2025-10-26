#ifndef TRABALHO_01_DEMO_H
#define TRABALHO_01_DEMO_H

#pragma once

#include "utils/sdl-application.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

class GraphicPrimitivesDemo final : public SdlApplication {
public:
    GraphicPrimitivesDemo() : SdlApplication("Primitivas gráficas - GC", WINDOW_WIDTH, WINDOW_HEIGHT) {}

protected:
    void on_render() override;
};

#endif //TRABALHO_01_DEMO_H