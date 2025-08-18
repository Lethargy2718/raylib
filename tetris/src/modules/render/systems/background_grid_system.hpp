#pragma once

#include <raylib.h>
#include "constants.hpp"

using namespace constants;

void drawGridBackground()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            DrawRectangleLines(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, {255, 255, 255, 50});
        }
    }
}
