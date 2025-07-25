#include <raylib.h>
#include "food.h"
#include "snake.h"
#include "game.h"

int main()
{
    const Color darkGreen = {20, 160, 133, 255};

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);

    Game g(25, screenWidth, screenHeight);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);

        if (g.run)
        {
            g.Update();
            g.Draw();
        }
        else
        {
            g.Draw();
            DrawText("Game Over", screenWidth / 2, screenHeight / 2, 20, WHITE);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            g.Reset();
    }

    CloseWindow();
}