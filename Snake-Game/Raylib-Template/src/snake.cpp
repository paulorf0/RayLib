#include "snake.h"

Snake::Snake(int size_, int scX_, int scY_)
{
    size = size_;
    scX = scX_;
    scY = scY_;
}
void Snake::Move()
{
    if (IsKeyDown(KEY_UP) && direction.y != 1)
        direction = {0, -1};
    else if (IsKeyDown(KEY_DOWN) && direction.y != -1)
        direction = {0, 1};
    else if (IsKeyDown(KEY_RIGHT) && direction.x != -1)
        direction = {1, 0};
    else if (IsKeyDown(KEY_LEFT) && direction.x != 1)
        direction = {-1, 0};
}

void Snake::Update()
{
    int gridWidth = scX / size;
    int gridHeight = scY / size;

    Vector2 newPos = Vector2Add(body[0], direction);

    if (newPos.x < 0)
        newPos.x = gridWidth - 1;

    if (newPos.x >= gridWidth)
        newPos.x = 0;

    if (newPos.y < 0)
        newPos.y = gridHeight - 1;

    if (newPos.y >= gridHeight)
        newPos.y = 0;

    body.push_front(newPos);
    body.pop_back();
}

void Snake::addTail()
{
    body.push_back(Vector2Subtract(body.back(), direction));
}

void Snake::Draw()
{
    for (size_t i = 0; i < body.size(); i++)
    {
        Rectangle rec = Rectangle{body[i].x * size, body[i].y * size, (float)size, (float)size};
        DrawRectangleRounded(rec, 0.5, 6, WHITE);
    }
}

bool Snake::headCollisionBody()
{

    Rectangle head = Rectangle{body[0].x * size, body[0].y * size, (float)size, (float)size};

    for (size_t i = 1; i < body.size(); i++)
    {
        Rectangle tail = Rectangle{body[i].x * size, body[i].y * size, (float)size, (float)size};
        if (CheckCollisionRecs(head, tail))
            return true;
    }

    return false;
}
