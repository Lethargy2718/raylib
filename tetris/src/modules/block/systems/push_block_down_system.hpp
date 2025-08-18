#pragma once

#include <raylib.h>
#include <flecs.h>
#include <array>
#include "block/components.hpp"
#include "block/utils/try_move.hpp"
#include <iostream>
#include "utils/constants.hpp"
#include "utils/rng.hpp"
#include "block/utils/add_block.hpp"

using namespace std;

inline void pushBlockDown(flecs::world &world, flecs::entity currentBlock)
{
    bool pushed = tryMove(world, currentBlock, 0, 1, false);
    if (pushed)
        return;
    currentBlock.remove<Current>();
    addBlock(world);
}