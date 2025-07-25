#include "game.h"

bool delay(double interval, double *lastTime)
{
    double currentTime = GetTime();
    if (currentTime - *lastTime >= interval)
    {
        *lastTime = currentTime;

        return true;
    }
    return false;
}

Game::Game(int snakeSize, int scX_, int scY_)
    : snake(snakeSize, scX_, scY_), food(scX_, scY_)
{
    scX = scX_;
    scY = scY_;
}

void Game::Draw()
{
    snake.Draw();
    food.Draw();
}

void Game::Reset()
{
    run = true;
    snake.body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    snake.direction = {1,0};
}

void Game::Update()
{
    if (delay(interval, &lastTime))
        snake.Update();
    snake.Move();

    Collision();
}

void Game::Collision()
{
    // Verifica se a cabeça da cobra colidiu com a comida (considerando ambos como quadrados)

    Rectangle snakeHead = {snake.body[0].x * snake.size, snake.body[0].y * snake.size, (float)snake.size, (float)snake.size};
    Rectangle foodRect = {food.pos.x, food.pos.y, (float)food.size, (float)food.size};

    if (CheckCollisionRecs(snakeHead, foodRect))
    {
        food.NewPos();
        snake.addTail();
    }

    if (snake.headCollisionBody())
        run = false;
}