#pragma once

#include "physics/components.hpp"
#include "renderer/components.hpp"
#include "center_to_rect.hpp"

inline void renderSystem(const Transform2D &t, const Sprite &s)
{
    Rectangle r = s.rect;
    Color color = {s.r, s.g, s.b, s.a};
    DrawRectanglePro({t.position.x, t.position.y, r.width, r.height}, {r.width / 2, r.height / 2}, t.rotation, color);
}