#pragma once

#include <flecs.h>
#include "block/components.hpp"
#include "block/utils/set_block_prefabs.hpp"
#include "input/input_system.hpp"
#include "block/components.hpp"

#include <iostream>
using namespace std;

struct input
{
    input(flecs::world &world)
    {
        world.module<input>();

        world.system()
            .with<Current>()
            .each([&world](flecs::entity e)
                  { playerInput(world, e); });
    }
};