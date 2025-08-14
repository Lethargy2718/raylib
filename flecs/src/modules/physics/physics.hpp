#pragma once

#include <flecs.h>
#include <raylib.h>
#include "physics/components.hpp"
#include "physics/systems/integrate_system.hpp"
#include "player/components.hpp"

struct physics
{
    physics(flecs::world world)
    {
        world.module<physics>();
        world.component<Transform2D>();
        world.component<Velocity>();

        world.system<Transform2D, const Velocity>()
            .each(integrate);
    }
};
