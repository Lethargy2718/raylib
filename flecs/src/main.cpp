#include <raylib.h>
#include <flecs.h>
#include "constants.hpp"
#include "renderer/components.hpp"

#include "input/input.hpp"
#include "physics/physics.hpp"
#include "coins/coins.hpp"
#include "collision/collision.hpp"
#include "ui/ui.hpp"
#include "renderer/renderer.hpp"
#include "player/player.hpp"

using namespace std;
using namespace constants;

int main()
{
    // Init window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Coin Test");
    SetTargetFPS(60);

    flecs::world world;

    const float spawnX = WINDOW_WIDTH / 2.0f;
    const float spawnY = WINDOW_HEIGHT / 2.0f;

    world.import <input>();
    world.import <physics>();
    world.import <player>();
    world.import <coins>();
    world.import <collision>();
    world.import <ui>();
    world.import <renderer>();

    world.entity(PLAYER_NAME)
        .add<Player>()
        .set<Transform2D>({{1, 1}, 0, {spawnX, spawnY}})
        .set<Velocity>({0, 0, 400.0f})
        .set<Sprite>({{spawnX, spawnY, TILE_SIZE, TILE_SIZE}, 255, 0, 0, 255});

    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        world.progress();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
