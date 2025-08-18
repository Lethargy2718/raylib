#pragma once

#include <flecs.h>
#include "grid/components.hpp"
#include <iostream>

using namespace std;

struct debug
{
    debug(flecs::world &world)
    {
        world.module<debug>();
        auto &grid = world.get<Grid>();

        world.system("debug").run([&](flecs::iter &) {});
    }
};
