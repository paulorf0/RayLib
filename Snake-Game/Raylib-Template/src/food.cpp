#include "food.h"

Food::Food(int scX_, int scY_)
{
    scX = scX_;
    scY = scY_;

    pos.x = rand() % (scX - size);
    pos.y = rand() % (scY - size);
}

void Food::NewPos()
{
    pos.x = rand() % (scX - size);
    pos.y = rand() % (scY - size);
}

void Food::Draw()
{
    Rectangle rec = Rectangle{pos.x, pos.y, (float)size, (float)size};
    DrawRectangleRounded(rec, 0.5, 6, BLACK);
}
