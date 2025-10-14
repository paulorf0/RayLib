#include "engine.h"

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
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