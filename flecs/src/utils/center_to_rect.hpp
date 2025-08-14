#pragma once

#include <raylib.h>
#include "physics/components.hpp"

inline Rectangle CenterToRect(const Transform2D t, const Rectangle r)
{
    float scaledW = r.width * t.scale.x;
    float scaledH = r.height * t.scale.y;

    return {t.position.x - scaledW / 2, t.position.y - scaledH / 2, scaledW, scaledH};
}