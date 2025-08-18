
#pragma once

#include <raylib.h>
#include <array>

using namespace std;

void setCells(array<array<int, 10>, 20> &grid, array<Vector2, 4> cells, int id)
{
    for (Vector2 vec2 : cells)
    {
        grid[static_cast<int>(vec2.x)][static_cast<int>(vec2.y)] = id;
    }
}