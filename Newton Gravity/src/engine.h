#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "ball.h"
#include <iostream>
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
   

    Engine(int amount);
    Engine(std::vector<Ball> balls);

    void update();
    void draw();

private:
    float G = 10000;

    std::vector<Ball> balls;

    CollisionResult computeVelocityAfterCollision(const Ball& b1, const Ball& b2);
    int getRandomInt(int min, int max);
};


#endif