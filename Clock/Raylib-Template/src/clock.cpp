#include "clock.h"

Clock::Clock(int size_, int sW_, int sH_) : size(size_), sW(sW_), sH(sH_)
{
    pos = Vector2{(float)sW / 2, (float)sH / 2};

    time_t now = time(0);
    tm *localTime = localtime(&now);
    minute = localTime->tm_min;
    hour = localTime->tm_hour % 12;
    secs = localTime->tm_sec;
}

void Clock::Update()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    minute = localTime->tm_min;
    hour = localTime->tm_hour % 12;
    secs = localTime->tm_sec;
}

void Clock::Draw()
{
    DrawFace();
    DrawHourBars();
    MinuteHand();
    HourHand();
    SecHand();

    DrawCircleV(pos, size / 40, RED);

}

void Clock::DrawFace()
{
    DrawCircleV(pos, size, GRAY);
}

void Clock::DrawHourBars()
{

    float rWidth = 5;
    float rHeight = size;

    for (int i = 0; i < 360; i += 30)
    {
        Rectangle rect = {pos.x, pos.y, rWidth, rHeight};
        DrawRectanglePro(rect, {rWidth / 2, rHeight}, i, BLACK);
    }

    for (int i = 0; i < 360; i += 6)
    {
        Rectangle rect = {pos.x, pos.y, rWidth - 3, rHeight};
        DrawRectanglePro(rect, {rWidth / 2, rHeight}, i, BLACK);
    }

    DrawCircleV(pos, size - 15, SKYBLUE);
}

void Clock::SecHand()
{
    float rWidth = 5;
    float rHeight = size * 0.95;

    float angle = 6 * secs;

    Rectangle rect = {pos.x, pos.y, rWidth, rHeight};
    DrawRectanglePro(rect, {rWidth / 2, rHeight}, angle, RED);
}

void Clock::HourHand()
{
    float rWidth = 5;
    float rHeight = size / 2;

    float angle = 30 * hour + 0.5 * minute;

    Rectangle rect = {pos.x, pos.y, rWidth, rHeight};
    DrawRectanglePro(rect, {rWidth / 2, rHeight}, angle, BLACK);
}

void Clock::MinuteHand()
{
    float rWidth = 5;
    float rHeight = size / 3;

    float angle = 6 * minute;

    Rectangle rect = {pos.x, pos.y, rWidth, rHeight};
    DrawRectanglePro(rect, {rWidth / 2, rHeight}, angle, BLACK);
}