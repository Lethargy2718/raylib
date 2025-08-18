#pragma once

#include <flecs.h>
#include <raylib.h>
#include "block/components.hpp"

void setBlockPrefabs(flecs::world &world)
{
    // Base prefab: every block shares these components
    auto blockPrefab = world.prefab("Block")
                           .add<Block>()
                           .add<BlockKind>()
                           .add<Rotation>()
                           .add<Offset>()
                           .add<Cells>()
                           .add<Id>();

    // Block I
    std::array<std::array<Vector2, 4>, 4> blocksIArr;
    blocksIArr[0] = {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}};
    blocksIArr[1] = {{{0, 2}, {1, 2}, {2, 2}, {3, 2}}};
    blocksIArr[2] = {{{2, 0}, {2, 1}, {2, 2}, {2, 3}}};
    blocksIArr[3] = {{{0, 1}, {1, 1}, {2, 1}, {3, 1}}};

    world.prefab("BlockI")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::I})
        .set<Offset>({{-1, 3}})
        .set<Cells>({blocksIArr})
        .set<Id>({0});

    // Block O
    std::array<std::array<Vector2, 4>, 4> blocksOArr;
    for (int i = 0; i < 4; ++i)
    {
        blocksOArr[i] = {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}};
    }

    world.prefab("BlockO")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::O})
        .set<Offset>({{0, 4}})
        .set<Cells>({blocksOArr})
        .set<Id>({1});

    // Block T
    std::array<std::array<Vector2, 4>, 4> blocksTArr;
    blocksTArr[0] = {{{0, 1}, {1, 0}, {1, 1}, {1, 2}}};
    blocksTArr[1] = {{{0, 1}, {1, 1}, {1, 2}, {2, 1}}};
    blocksTArr[2] = {{{1, 0}, {1, 1}, {1, 2}, {2, 1}}};
    blocksTArr[3] = {{{0, 1}, {1, 0}, {1, 1}, {2, 1}}};

    world.prefab("BlockT")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::T})
        .set<Offset>({{0, 3}})
        .set<Cells>({blocksTArr})
        .set<Id>({2});

    // Block S
    std::array<std::array<Vector2, 4>, 4> blocksSArr;
    blocksSArr[0] = {{{0, 1}, {0, 2}, {1, 0}, {1, 1}}};
    blocksSArr[1] = {{{0, 1}, {1, 1}, {1, 2}, {2, 2}}};
    blocksSArr[2] = {{{1, 1}, {1, 2}, {2, 0}, {2, 1}}};
    blocksSArr[3] = {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}};

    world.prefab("BlockS")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::S})
        .set<Offset>({{0, 3}})
        .set<Cells>({blocksSArr})
        .set<Id>({3});

    // Block Z
    std::array<std::array<Vector2, 4>, 4> blocksZArr;
    blocksZArr[0] = {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}};
    blocksZArr[1] = {{{0, 2}, {1, 1}, {1, 2}, {2, 1}}};
    blocksZArr[2] = {{{1, 0}, {1, 1}, {2, 1}, {2, 2}}};
    blocksZArr[3] = {{{0, 1}, {1, 0}, {1, 1}, {2, 0}}};

    world.prefab("BlockZ")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::Z})
        .set<Offset>({{0, 3}})
        .set<Cells>({blocksZArr})
        .set<Id>({4});

    // Block J
    std::array<std::array<Vector2, 4>, 4> blocksJArr;
    blocksJArr[0] = {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}};
    blocksJArr[1] = {{{0, 1}, {0, 2}, {1, 1}, {2, 1}}};
    blocksJArr[2] = {{{1, 0}, {1, 1}, {1, 2}, {2, 2}}};
    blocksJArr[3] = {{{0, 1}, {1, 1}, {2, 0}, {2, 1}}};

    world.prefab("BlockJ")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::J})
        .set<Offset>({{0, 3}})
        .set<Cells>({blocksJArr})
        .set<Id>({5});

    // Block L
    std::array<std::array<Vector2, 4>, 4> blocksLArr;
    blocksLArr[0] = {{{0, 2}, {1, 0}, {1, 1}, {1, 2}}};
    blocksLArr[1] = {{{0, 1}, {1, 1}, {2, 1}, {2, 2}}};
    blocksLArr[2] = {{{1, 0}, {1, 1}, {1, 2}, {2, 0}}};
    blocksLArr[3] = {{{0, 0}, {0, 1}, {1, 1}, {2, 1}}};

    world.prefab("BlockL")
        .is_a(blockPrefab)
        .set<BlockKind>({BlockType::L})
        .set<Offset>({{0, 3}})
        .set<Cells>({blocksLArr})
        .set<Id>({6});
}
