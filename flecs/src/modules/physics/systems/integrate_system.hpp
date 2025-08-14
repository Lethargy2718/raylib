#pragma once
#include <flecs.h>
#include "../components.hpp"

inline void integrate(Transform2D &t, const Velocity &v)
{
    t.position.x += v.x * v.speed * GetFrameTime();
    t.position.y += v.y * v.speed * GetFrameTime();
}