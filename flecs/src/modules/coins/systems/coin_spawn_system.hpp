#pragma once

#include <flecs.h>
#include "rng.hpp"
#include "constants.hpp"
#include "renderer/components.hpp"
#include "coins/components.hpp"
#include "physics/components.hpp"

using namespace constants;

inline void spawnCoin(const flecs::world &world)
{
    const float px = rng::real(TILE_SIZE, WINDOW_WIDTH - TILE_SIZE);
    const float py = rng::real(TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE);

    world.entity()
        .add<Coin>()
        .set<Transform2D>({{1, 1}, 0, {px, py}})
        .set<Sprite>({{px, py, TILE_SIZE, TILE_SIZE}, 255, 255, 0, 255});
}