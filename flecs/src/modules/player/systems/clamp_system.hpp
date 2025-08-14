#pragma once

#include "physics/components.hpp"
#include "constants.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace constants;

inline void clampPosition(Transform2D &t, const Rectangle &r)
{
    t.position.x = clamp(t.position.x, r.width / 2, WINDOW_WIDTH - r.width / 2);
    t.position.y = clamp(t.position.y, r.height / 2, WINDOW_HEIGHT - r.height / 2);
}