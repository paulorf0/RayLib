#include <raylib.h>
#include <raymath.h>
#include "clock.h"

int main()
{
    const Color darkGreen = {20, 160, 133, 255};

    constexpr int sW = 800;
    constexpr int sH = 600;

    InitWindow(sW, sH, "My first RAYLIB program!");
    SetTargetFPS(60);

    Clock clock(250, sW, sH);
    while (!WindowShouldClose())
    {

        clock.Update();

        BeginDrawing();
        ClearBackground(darkGreen);
        clock.Draw();
        EndDrawing();
    }

    CloseWindow();
}