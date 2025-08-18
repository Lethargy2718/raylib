#pragma once

#include <flecs.h>
#include "grid/components.hpp"

struct grid
{
    grid(flecs::world &world)
    {
        world.module<grid>();

        world.set<Grid>({{{0}}});

        auto &cells = world.get_mut<Grid>().cells;
    }
};
