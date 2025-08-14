#pragma once

#include <raylib.h>
#include <string>
#include "constants.hpp"
#include "../singleton.hpp"

inline void drawScore()
{
    std::string text = "Score: " + std::to_string(gameState.score);
    int fontSize = 20;
    int textWidth = MeasureText(text.c_str(), fontSize);
    int posX = (constants::WINDOW_WIDTH - textWidth) / 2;
    int posY = 10;
    DrawText(text.c_str(), posX, posY, fontSize, BLACK);
}