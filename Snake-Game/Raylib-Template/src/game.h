#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "snake.h"
#include "food.h"

class Game
{
public:
    Snake snake;
    Food food;

    int scX, scY;

    bool run = true;

    Game(int snakeSize, int scX, int scY);
    void Update();
    void Draw();
    void Reset();
    void Collision();

private:
    double lastTime = 0.;
    double interval = 0.1;
};