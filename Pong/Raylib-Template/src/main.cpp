#include <raylib.h>
#include <thread>
#include "ball.h"
#include "pad.h"

int main(int argc, char const *argv[])
{

    int scX = 1280;
    int scY = 800;

    int w = 10 + 30, h = 100;

    InitWindow(scX, scY, "Test1");
    SetTargetFPS(60);

    Ball b(300, 300, 10, 10, scX, scY, h, w, 20);
    Pad player1(h, w, scY / 2, 0, 6, KEY_W, KEY_S);
    Pad player2(h, w, scY / 2, scX - w, 6, KEY_UP, KEY_DOWN);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        // 1. Event Handler
        b.Update(player1.posY, player2.posY);

        std::thread t1([&]()
                       { player1.Update(); });
        std::thread t2([&]()
                       { player2.Update(); });

        t1.join();
        t2.join();

        // 2.Update positions

        ClearBackground(BLACK);
        b.Draw();
        player1.Draw();
        player2.Draw();

        DrawLine(scX/2, 0, scX/2, scY, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
