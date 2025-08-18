#pragma once

#include <raylib.h>
#include <array>

using namespace std;

// Block tag
struct Block
{
};

// Current block tag
struct Current
{
};

// Block type enum
enum class BlockType
{
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

struct BlockKind
{
    BlockType type;
};

struct Rotation
{
    int rotation = 0;
};

// Offset on the grid
struct Offset
{
    Vector2 offset = {0, 0};
};

// Rotations
struct Cells
{
    array<array<Vector2, 4>, 4> cells;
};

struct Id
{
    int id;
};