#pragma once

#include <flecs.h>
#include "input/systems/input_system.hpp"
#include "physics/components.hpp"
#include "player/components.hpp"
#include "renderer/components.hpp"
#include "renderer/systems/render_system.hpp"

struct renderer
{
    renderer(flecs::world world)
    {
        world.module<renderer>();
        world.component<Sprite>();

        world.system<const Transform2D, const Sprite>()
            .each(renderSystem);
    }
};