#pragma once
#include <raylib.h>

class Pad
{
public:
    int height, width;
    int scX, scY;
    int speed;
    double posY, posX;
    KeyboardKey up, down;


    Pad(int height, int width, double posY, double posX,int speed, KeyboardKey up, KeyboardKey down);
    void Update();
    void Draw();
    
};