#pragma once

#include <raylib.h>
#include <flecs.h>
#include <array>

#include "block/utils/try_move.hpp"
#include "block/components.hpp"
#include "grid/utils/is_invalid.hpp"
#include "block/utils/get_block_cells.hpp"
#include "grid/utils/set_cells.hpp"
#include "grid/utils/clear_cells.hpp"
#include "grid/components.hpp"
#include "block/utils/rotate.hpp"

#include <iostream>
using namespace std;

inline void playerInput(flecs::world &world, flecs::entity currentBlock)
{

    int dx = 0;
    bool doRotate = false;

    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
        dx = -1;
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
        dx = 1;
    if (IsKeyPressed(KEY_R))
        doRotate = true;

    tryMove(world, currentBlock, dx, 0, doRotate);
}
