#include "engine.h"

int main() 
{
    const Color dark = {0, 0, 0, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 800;
    
    Ball ball1(15, 100.0f, {400, 400}, {0, 0});
    Ball ball2(15, 100.f, {400, 200}, {0, 0});
    Ball ball3(15, 100.f, {200, 400}, {0, 0 });
    // Ball ball4(15, 100.f, {550, 400}, {0, -3});

    std::vector<Ball> balls {ball1, ball2, ball3};
    Engine engine(balls);
    
    InitWindow(screenWidth, screenHeight, "Gravity");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        engine.update();    
        
        BeginDrawing();
            ClearBackground(dark);
            engine.draw();
        EndDrawing();
    }
    
    CloseWindow();
}