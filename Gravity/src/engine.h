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
    Engine(int amount, int screen_height, int screen_width);
    ~Engine();

    void update();
    void draw();

    void logCollisionVelocity(float velocity);
    void saveVelocityData();


private:
    float t;
    std::vector<float> collisionVelocities; 
    std::string velocityLogFile = "velocityLog.csv";


    std::vector<Ball> objects;
    float kinectEnergySystem;
    Vector2 GRAVITY;


    int const screen_width ;
    int const screen_height;
    
    void collision();
    void gravity();
    int getRandomInt(int min, int max);

    CollisionResult computeVelocityAfterCollision(Ball b1, Ball b2);
};


#endif