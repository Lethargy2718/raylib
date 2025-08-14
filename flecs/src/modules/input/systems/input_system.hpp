#pragma once

#include <raylib.h>
#include <cmath>
#include "physics/components.hpp"

inline void playerInput(Velocity &v)
{
    v.x = 0;
    v.y = 0;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        v.y = -1;
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        v.y = 1;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        v.x = -1;
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        v.x = 1;

    // Normalize movement
    if (v.x == 0 && v.y == 0)
        return;
    float scale = 1 / sqrt(v.x * v.x + v.y * v.y);
    v.x *= scale;
    v.y *= scale;
}
