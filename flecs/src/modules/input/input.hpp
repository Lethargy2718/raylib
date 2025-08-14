#pragma once

#include <flecs.h>
#include "input/systems/input_system.hpp"
#include "physics/components.hpp"
#include "player/components.hpp"

struct input
{
    input(flecs::world &world)
    {
        world.module<input>();

        world.system<Velocity>()
            .with<Player>()
            .each([](Velocity &v)
                  { playerInput(v); });
    }
};
