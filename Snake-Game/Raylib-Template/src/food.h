#pragma once
#include <cstdlib>
#include <raylib.h>
class Food
{
public:
    Vector2 pos;
    int size = 20;
    int scX, scY;

    Food(int scX_, int scY_);
    void NewPos();
    void Draw();
};