#include <raylib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640
#define LEVEL_WIDTH 10
#define LEVEL_HEIGHT 10
#define TILE_SIZE 64
#define OFFSET 0.1f
#define GRAVITY 5e3

#define DEBUG true
#define DEBUG_THICKNESS 2

using namespace std;

struct Sprite
{
    Texture2D texture;
    Rectangle rect;
};

struct Player
{
    Sprite sprite;
    Rectangle hitbox;
    Vector2 v;   
    float speed;
};

typedef vector<int> vi;
typedef vector<Sprite> vst;

vector<vi> level = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


// Velocity
void applyInput(Player *player) {
    player->v.x = 0;
    
    if (IsKeyDown(KEY_A)) {
        player->v.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        player->v.x = 1;
    }    
    if (IsKeyPressed(KEY_W)) {
        player->v.y = -1100;
    }
}

void applyGravity(Player *player) {
    auto &v = player->v;
    // vy += a * dt
    v.y += GRAVITY * GetFrameTime();
    v.y = min(v.y, 1500.0f);
}

void applyVelocityX(Player *player) {
    // px += vx * dt
    player->sprite.rect.x += player->v.x * player->speed * GetFrameTime(); 
}

void applyVelocityY(Player *player) {
    // py += vy * dt
    player->sprite.rect.y += player->v.y * GetFrameTime();
}

// Hitbox
float getOffsetX(Player *player) {
    return player->sprite.rect.width * OFFSET;
}

float getOffsetY(Player *player) {
    return player->sprite.rect.height * OFFSET;
}

void createHitbox(Player *player) {
    float offsetX = getOffsetX(player);
    float offsetY = getOffsetY(player);
    float width  = player->sprite.rect.width * (1 - 2 * OFFSET);
    float height = player->sprite.rect.height * (1 - 2 * OFFSET);

    player->hitbox = (Rectangle){player->sprite.rect.x + offsetX, player->sprite.rect.y + offsetY, width, height};
}

void updateHitboxY(Player *player) {
    float offsetY = getOffsetY(player);
    player->hitbox.y = player->sprite.rect.y + offsetY;
}

void updateHitboxX(Player *player) {
    float offsetX = getOffsetX(player);
    player->hitbox.x = player->sprite.rect.x + offsetX;
}

// Limit
void limitPlayer(Player *p) {
    auto &r = p->sprite.rect;
    float oldX = r.x;
    float oldY = r.y;
    
    r.x = clamp(r.x, 0.0f, GetScreenWidth() - r.width);
    if (r.x != oldX) p->v.x = 0.0f;
    
    r.y = clamp(r.y, 0.0f, GetScreenHeight() - r.height);
    if (r.y != oldY) p->v.y = 0.0f;
}

// Collision
void checkCollisionY(Player *player, vst &tiles) {
    auto &hb = player->hitbox;
    float offsetY = getOffsetY(player);

    for (const auto &tile : tiles) {
        if (!CheckCollisionRecs(hb, tile.rect)) continue;

        if (player->v.y > 0) hb.y = tile.rect.y - hb.height;
        else hb.y = tile.rect.y + tile.rect.height;

        player->sprite.rect.y = hb.y - offsetY;
        player->v.y = 0;

        break;
    }
}

void checkCollisionX(Player *player, vst &tiles) {
    auto &hb = player->hitbox;
    float offsetX = getOffsetX(player);

    for (const auto &tile : tiles) {
        if (!CheckCollisionRecs(hb, tile.rect)) continue;

        if (player->v.x > 0) hb.x = tile.rect.x - hb.width;
        else hb.x = tile.rect.x + tile.rect.width;

        player->sprite.rect.x = hb.x - offsetX;
        player->v.x = 0;

        break;
    }
}

// Movement
void movePlayer(Player *player, vst &tiles) {
    applyInput(player);
    applyGravity(player);
    
    // Y
    applyVelocityY(player);
    updateHitboxY(player);
    checkCollisionY(player, tiles);

    // X
    applyVelocityX(player);
    updateHitboxX(player);
    checkCollisionX(player, tiles);
    
    limitPlayer(player);
}

// Draw
void drawPlayer(Player &player) {
    static int signX = 1; // Shared by all function calls
    signX = (player.v.x == 0) ? signX : ((player.v.x > 0) ? 1 : -1);
    DrawTexturePro(player.sprite.texture, {0,0, 16.0f * signX ,16.0f}, player.sprite.rect, {0,0}, 0, RAYWHITE);
}

// Debug
void debugDrawPlayerBorder(Player player) {
    DrawRectangleLinesEx(player.sprite.rect, DEBUG_THICKNESS, RED);
}

void debugDrawPlayerHitboxBorder(Player player) {
    DrawRectangleLinesEx(player.hitbox, DEBUG_THICKNESS, BLACK);
}

// Level
vst loadLevel(vector<vi> level, Texture texture) {
    vst sprites;

    for (size_t i = 0; i < level.size(); i++) {
        for (size_t j = 0; j < level[i].size(); j++) {
            if (level[i][j] == 0) continue;
            sprites.emplace_back((Sprite){texture, {static_cast<float>(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE), TILE_SIZE, TILE_SIZE}});
        }
    }

    return sprites;
}

void drawLevel(vst sprites) {
    for (const auto &sprite : sprites) {
        DrawTexturePro(sprite.texture, {TILE_SIZE, 0, TILE_SIZE, TILE_SIZE}, sprite.rect, {0,0}, 0, RAYWHITE);
    }
}

int main()
{
    // Init
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World");

    // Textures
    Texture playerIdleTexture = LoadTexture("assets/hero/herochar_idle_anim_strip_4.png");
    string tilePath = "assets/tiles/tileset" + to_string(TILE_SIZE) + ".png";
    Texture tileTexture = LoadTexture(tilePath.c_str());

    // Player
    Sprite playerSprite{playerIdleTexture, {1 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE}};
    Player player{playerSprite, {0,0,0,0}, {0,0}, 300.0};
    createHitbox(&player);

    // Level
    vst loadedLevel = loadLevel(level, tileTexture);

    // Gameloop
    while (!WindowShouldClose())
    {
        // Update
        movePlayer(&player, loadedLevel);

        // Draw
        BeginDrawing();

        ClearBackground(SKYBLUE);

        drawLevel(loadedLevel);
        drawPlayer(player);

        // Debug
        if (DEBUG) {
            debugDrawPlayerBorder(player);
            debugDrawPlayerHitboxBorder(player);
        }

        EndDrawing();
    }

    // Terminate
    UnloadTexture(playerIdleTexture);
    UnloadTexture(tileTexture);
    CloseWindow();
    return 0;
}
