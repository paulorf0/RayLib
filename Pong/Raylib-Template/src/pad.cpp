#include "pad.h"

Pad::Pad(int height_, int width_, double posY_, double posX_, int speed_, KeyboardKey up_, KeyboardKey down_)
{
    height = height_;
    width = width_;
    posY = posY_;
    posX = posX_;
    up = up_;
    down = down_;
    speed = speed_;
    scY = GetScreenHeight();
    scX = GetScreenWidth();
}

void Pad::Update()
{

    if (IsKeyDown(up))
    {
        if (posY - speed <= 0)
            return;

        posY -= speed;
    }
    if (IsKeyDown(down))
    {
        if (posY + height + speed >= scY)
            return;

        posY += speed;
    }
}

void Pad::Draw()
{
    DrawRectangle(posX, posY, width, height, WHITE);
}