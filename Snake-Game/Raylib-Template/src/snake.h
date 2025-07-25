#pragma once

#include <stack>
#include <raylib.h>
#include <raymath.h>

class Snake
{
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};

    float x, y;
    int size;
    int scX, scY;
    int speed;
    Snake(int size_, int scX_, int scY_);
    void Move();
    void Update();
    void addTail();
    void Draw();
    bool headCollisionBody();
};