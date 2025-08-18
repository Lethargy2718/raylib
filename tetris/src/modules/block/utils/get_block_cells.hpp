#pragma once

#include <raylib.h>
#include <array>

using namespace std;

array<Vector2, 4> getBlockCells(array<array<Vector2, 4>, 4> allCells, Vector2 offset, int rotation)
{
    array<Vector2, 4> currentCells = allCells[rotation];
    for (int i = 0; i < 4; i++)
    {
        currentCells[i].x += offset.y;
        currentCells[i].y += offset.x;
    }
    return currentCells;
}