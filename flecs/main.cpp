#include <raylib.h>
#include <flecs.h>
#include <iostream>
#include <rng.hpp>
#include <algorithm>

using namespace std;

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 640;
constexpr int TILE_SIZE = 32; // 20x20 grid

static int score = 0;

// Components
struct Transform2D
{
    Vector2 scale;
    float rotation;
    Vector2 position;
};

struct Velocity
{
    float x;
    float y;
    float speed;
};

struct Sprite
{
    Rectangle rect;
    unsigned char r, g, b, a;
};

// Tags
struct Player
{
};

struct Coin
{
};

// Systems
void takeInput(Velocity &v)
{
    v.x = 0;
    v.y = 0;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        v.y = -1;
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        v.y = 1;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        v.x = -1;
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        v.x = 1;

    // Normalize movement
    if (v.x == 0 && v.y == 0)
        return;
    float scale = 1 / sqrt(v.x * v.x + v.y * v.y);
    v.x *= scale;
    v.y *= scale;
}

void integrate(Transform2D &t, const Velocity &v)
{
    t.position.x += v.x * v.speed * GetFrameTime();
    t.position.y += v.y * v.speed * GetFrameTime();
}

void clampPosition(Transform2D &t)
{
    t.position.x = std::clamp(t.position.x, 0.f, static_cast<float>(WINDOW_WIDTH));
    t.position.y = std::clamp(t.position.y, 0.f, static_cast<float>(WINDOW_HEIGHT));
}

void spawnCoin(const flecs::world &world)
{
    const float px = rng::real(TILE_SIZE, WINDOW_WIDTH - TILE_SIZE);
    const float py = rng::real(TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE);

    world.entity()
        .add<Coin>()
        .set<Transform2D>({{1, 1}, 0, {px, py}})
        .set<Sprite>({{px, py, TILE_SIZE, TILE_SIZE}, 255, 255, 0, 255});
}

void handleCollision(flecs::entity &p, flecs::entity &e)
{
    auto &cTransform = e.get<Transform2D>();
    auto &cSprite = e.get<Sprite>();

    auto &pTransform = p.get<Transform2D>();
    auto &pSprite = p.get<Sprite>();

    // Move origin from center to top left
    Rectangle coinRect = {
        cTransform.position.x - (cSprite.rect.width * cTransform.scale.x) / 2,
        cTransform.position.y - (cSprite.rect.height * cTransform.scale.y) / 2,
        cSprite.rect.width * cTransform.scale.x,
        cSprite.rect.height * cTransform.scale.y};

    Rectangle playerRect = {
        pTransform.position.x - (pSprite.rect.width * pTransform.scale.x) / 2,
        pTransform.position.y - (pSprite.rect.height * pTransform.scale.y) / 2,
        pSprite.rect.width * pTransform.scale.x,
        pSprite.rect.height * pTransform.scale.y};

    if (CheckCollisionRecs(playerRect, coinRect))
    {
        score++;
        e.destruct();
    }
}

void renderSystem(const Transform2D &t, const Sprite &s)
{
    Color color = {s.r, s.g, s.b, s.a};

    float width = s.rect.width * t.scale.x;
    float height = s.rect.height * t.scale.y;

    Vector2 origin = {width / 2.0f, height / 2.0f};

    Rectangle rect = {t.position.x - origin.x, t.position.y - origin.y, width, height};

    DrawRectanglePro(rect, origin, t.rotation, color);
}

// Helpers
void drawScore()
{
    string text = "Score: " + to_string(score);
    int fontSize = 20;
    int textWidth = MeasureText(text.c_str(), fontSize);
    int posX = (WINDOW_WIDTH - textWidth) / 2;
    int posY = 10;
    DrawText(text.c_str(), posX, posY, fontSize, BLACK);
}

int main()
{
    // Init window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Coin Test");
    SetTargetFPS(60);

    flecs::world world;

    const float spawnX = WINDOW_WIDTH / 2.0f - TILE_SIZE / 2;
    const float spawnY = WINDOW_HEIGHT / 2.0f - TILE_SIZE / 2;

    auto player = world.entity("Player")
                      .add<Player>()
                      .set<Transform2D>({{1, 1}, 0, {spawnX, spawnY}})
                      .set<Velocity>({0, 0, 400.0f})
                      .set<Sprite>({{spawnX, spawnY, TILE_SIZE, TILE_SIZE}, 255, 0, 0, 255});

    world.system<Velocity>()
        .with<Player>()
        .each(takeInput);

    world.system<Transform2D, const Velocity>()
        .each(integrate);

    world.system<Transform2D>()
        .each([](flecs::entity e, Transform2D &t)
              { clampPosition(t); });

    world.system<>()
        .interval(2.0)
        .each([&world]()
              { spawnCoin(world); });

    world.system<Coin>()
        .each([&player](flecs::entity coin_entity, const Coin &)
              { handleCollision(player, coin_entity); });

    world.system<const Transform2D, const Sprite>()
        .each(renderSystem);

    // Game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);

        world.progress();

        drawScore();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
