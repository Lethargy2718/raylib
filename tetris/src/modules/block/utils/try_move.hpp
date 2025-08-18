#pragma once

#include <raylib.h>
#include <flecs.h>
#include <array>
#include "block/components.hpp"
#include "grid/utils/is_invalid.hpp"
#include "block/utils/get_block_cells.hpp"
#include "grid/utils/set_cells.hpp"
#include "grid/utils/clear_cells.hpp"
#include "grid/components.hpp"
#include "block/utils/rotate.hpp"

bool tryMove(flecs::world &world, flecs::entity currentBlock, int dx, int dy, bool doRotate)
{
    const auto &allCells = currentBlock.get<Cells>().cells;
    auto &offset = currentBlock.get_mut<Offset>().offset;
    auto &rotation = currentBlock.get_mut<Rotation>().rotation;
    auto &grid = world.get_mut<Grid>().cells;

    Vector2 newOffset = offset;
    int newRotation = rotation;

    newOffset.x += dx;
    newOffset.y += dy;
    newRotation = (rotation + doRotate) % 4;

    auto newCells = getBlockCells(allCells, newOffset, newRotation);
    auto oldCells = getBlockCells(allCells, offset, rotation);

    if (isInvalid(grid, oldCells, newCells))
        return false;

    offset = newOffset;
    rotation = newRotation;

    // Clear old, set new
    clearCells(grid, oldCells);
    setCells(grid, newCells, currentBlock.get<Id>().id);

    return true;
}