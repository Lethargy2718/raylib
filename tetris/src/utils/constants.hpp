#pragma once

#include <raylib.h>
#include <array>
#include <string>

namespace constants
{
    constexpr int WINDOW_WIDTH = 300;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr int TILE_SIZE = 30;
    constexpr std::array<const char *, 7> BLOCK_PREFABS = {
        "block::BlockI",
        "block::BlockO",
        "block::BlockT",
        "block::BlockS",
        "block::BlockZ",
        "block::BlockJ",
        "block::BlockL"};

}
