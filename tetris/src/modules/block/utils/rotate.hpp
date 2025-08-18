#pragma once

inline void rotate(int &rotation)
{
    rotation = ++rotation % 4;
}

inline void unRotate(int &rotation)
{
    rotation = (--rotation % 4 + 4) % 4;
}