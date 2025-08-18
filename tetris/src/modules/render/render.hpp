#pragma once

#include <flecs.h>
#include "render/systems/background_grid_system.hpp"
#include "render/systems/draw_blocks.hpp"
#include "grid/components.hpp"

struct render
{
    render(flecs::world &world)
    {
        world.module<render>();

        world.system().run([](flecs::iter &)
                           { drawGridBackground(); });

        world.system().run([&world](flecs::iter &)
                           { drawBlocks(world.get<Grid>().cells); });
    }
};
