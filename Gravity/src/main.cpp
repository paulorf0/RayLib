#include "engine.h"

int main() 
{
    const Color darkGreen = {0, 0, 0, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 800;
    
    Engine engine(20, screenHeight, screenWidth);
    
    InitWindow(screenWidth, screenHeight, "Collision");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        engine.update();    
        
        BeginDrawing();
            ClearBackground(darkGreen);
            engine.draw();
        EndDrawing();
    }
    
    CloseWindow();
}