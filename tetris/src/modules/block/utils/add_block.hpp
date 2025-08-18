#pragma once

#include <flecs.h>
#include "utils/constants.hpp"
#include "utils/rng.hpp"
#include "block/components.hpp"
#include "grid/utils/set_cells.hpp"
#include "grid/components.hpp"

#include <iostream>
using namespace std;

bool addBlock(flecs::world &world)
{
    flecs::entity e = world.entity().is_a(world.lookup(constants::BLOCK_PREFABS[rng::integer(0, 6)])).add<Current>();

    cout << e.get_mut<Cells>().cells[0][0].x; // e doesn't have components here. make the system immediate.
    return true;
    setCells(world.get_mut<Grid>().cells, e.get<Cells>().cells[0], e.get<Id>().id);
}