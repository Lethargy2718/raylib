#pragma once

#include <raylib.h>
#include "render/render_constants.hpp"
#include "constants.hpp"
#include <array>

using namespace std;
using namespace constants;

void drawBlocks(const array<array<int, 10>, 20> &grid)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] == 0)
                continue;
            Color c = blockToColor[grid[i][j]];
            DrawRectangle(j * TILE_SIZE + 1, i * TILE_SIZE + 1, TILE_SIZE - 1, TILE_SIZE - 1, c);
        }
    }
}
