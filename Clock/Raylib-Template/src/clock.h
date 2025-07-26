#pragma once
#include <raylib.h>
#include <raymath.h>
#include <ctime>
#include <iostream>

class Clock
{
public:
    Vector2 pos;
    int size, sW, sH;

    int minute;
    int hour;
    int secs;

    Clock(int size_, int sW_, int sH_);
    void Draw();
    void Update();
    void DrawFace();
    void SecHand();
    void DrawHourBars();
    void HourHand();
    void MinuteHand();

};