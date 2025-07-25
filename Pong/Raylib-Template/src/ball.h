#pragma once
#include <raylib.h>
#include <iostream>
class Ball
{
public:
    double x, y, speedX, speedY;
    int radius, height, width;
    int screenX, screenY;
    Ball(double x_, double y_, double speedX_, double speedY_, int screenX_, int screenY_, int height_, int width_, int radius_);
    void Update(double p1Y, double p2Y);
    void Draw();

private:
    int error = 0.5;
};