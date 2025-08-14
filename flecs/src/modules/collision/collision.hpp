#pragma once

#include <flecs.h>
#include "collision/systems/collision_system.hpp"
#include "physics/components.hpp"
#include "player/components.hpp"
#include "coins/components.hpp"

struct collision
{
    collision(flecs::world &world)
    {
        world.module<collision>();

        world.system<Coin>()
            .each([](flecs::entity c, Coin)
                  { handleCollision(c); });
    }
};
