#pragma once

#include <raylib.h>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

bool isInvalid(array<array<int, 10>, 20> &grid, array<Vector2, 4> oldCells, array<Vector2, 4> newCells)
{
    for (const auto &[fx, fy] : newCells)
    {
        int x = static_cast<int>(fx);
        int y = static_cast<int>(fy);

        if (x < 0 || x >= 20 || y < 0 || y >= 10)
            return true;
        if (grid[x][y] != 0)
        {
            auto oldCellIt = find_if(oldCells.begin(), oldCells.end(), [&](const Vector2 oldVec)
                                     { return oldVec.x == x && oldVec.y == y; });
            if (oldCellIt == oldCells.end())
                return true;
        }
    }
    return false;
}