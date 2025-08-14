#pragma once

#include <raylib.h>

struct Transform2D
{
    Vector2 scale = {1, 1};
    float rotation = 0;
    Vector2 position = {0, 0};
};

struct Velocity
{
    float x;
    float y;
    float speed;
};