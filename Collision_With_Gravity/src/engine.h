#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "ball.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <random> 
#include <chrono> 


struct CollisionResult{
    Vector2 new_b1_vel;
    Vector2 new_b2_vel;
};

class Engine{
public:
    int screen_width;
    int screen_height;

    Engine(int amount, int screen_height, int screen_width);

    void update();
    void draw();

private:
    float timeVelocity = 1.5;

    std::vector<Ball> objects;
    Vector2 GRAVITY = {0, 98.f*1.5f};
    float kinectEnergySystem;

    void collision();
    int getRandomInt(int min, int max);

    CollisionResult computeVelocityAfterCollision(Ball b1, Ball b2);
    void randomBalls(int amount);
    void customBalls();
};


#endif