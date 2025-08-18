#pragma once

#include <flecs.h>
#include "block/components.hpp"
#include "block/utils/set_block_prefabs.hpp"
#include "block/systems/push_block_down_system.hpp"

struct block
{
    block(flecs::world &world)
    {
        world.module<block>();
        setBlockPrefabs(world);
        world.entity().is_a(world.lookup("BlockZ")).add<Current>();
        world.system().with<Current>().interval(0.1f).each([&world](flecs::entity currBlock)
                                                           { pushBlockDown(world, currBlock); });
    }
};
