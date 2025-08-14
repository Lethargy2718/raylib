#pragma once

#include <flecs.h>
#include "player/components.hpp"
#include "player/systems/clamp_system.hpp"
#include "renderer/components.hpp"
#include "coins/components.hpp"
#include <iostream>

struct player
{
    player(flecs::world &world)
    {
        world.module<player>();
        world.component<Player>();

        world.system<Transform2D, Sprite>()
            .with<Player>()
            .each([](Transform2D &t, Sprite &s)
                  { clampPosition(t, s.rect); });
    }
};
