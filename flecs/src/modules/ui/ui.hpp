#pragma once

#include <flecs.h>
#include "ui/systems/score_system.hpp"

struct ui
{
    ui(flecs::world world)
    {
        world.module<ui>();

        world.system<>().run([](flecs::iter &)
                             { drawScore(); });
    }
};
