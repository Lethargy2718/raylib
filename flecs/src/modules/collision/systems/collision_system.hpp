#pragma once

#include <flecs.h>
#include <raylib.h>
#include "physics/components.hpp"
#include "renderer/components.hpp"
#include "center_to_rect.hpp"
#include "../singleton.hpp"
#include "constants.hpp"

inline void handleCollision(flecs::entity &e)
{
    flecs::entity p = e.world().lookup(constants::PLAYER_NAME);
    if (!p.is_valid())
        return;

    auto &cTransform = e.get<Transform2D>();
    auto &cRect = e.get<Sprite>().rect;

    auto &pTransform = p.get<Transform2D>();
    auto &pRect = e.get<Sprite>().rect;

    // Move origin from center to top left
    Rectangle coinRect = CenterToRect(cTransform, cRect);
    Rectangle playerRect = CenterToRect(pTransform, pRect);

    if (CheckCollisionRecs(playerRect, coinRect))
    {
        gameState.score++;
        e.destruct();
    }
}