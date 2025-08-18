#include <raylib.h>
#include <flecs.h>
#include "constants.hpp"

#include "grid/grid.hpp"
#include "input/input.hpp"
#include "block/block.hpp"
#include "render/render.hpp"
#include "debug/debug.hpp"

using namespace std;
using namespace constants;

constexpr bool DEBUG = false;

int main()
{
    // Init window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    SetTargetFPS(60);

    flecs::world world;

    world.import <grid>();
    world.import <block>();
    world.import <render>();
    world.import <input>();
    if (DEBUG)
        world.import <debug>();

    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        world.progress();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}