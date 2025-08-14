#pragma once

#include <flecs.h>
#include "coins/components.hpp"
#include "coins/systems/coin_spawn_system.hpp"

struct coins
{
    coins(flecs::world &world)
    {
        world.module<coins>();
        world.component<Coin>();

        world.system<>()
            .interval(2.0)
            .each([&world]()
                  { spawnCoin(world); });
    }
};
