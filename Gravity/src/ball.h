
#pragma once
#ifndef BALL_H
#define BALL_H
 
#include <raylib.h>
#include <raymath.h>

class Ball
{
public:
    Ball(float posx, float posy);
    void update();
    void draw() const;

    Vector2 getPos();
    void setPos(Vector2 newPos);

    Vector2 getVel();
    void setVel(Vector2 vel);    
    

    void calcKinectEnergy();
    float getKinectEnergy();

    int getMass();
    int getRadius();

private:
    float kinectEnergy;

    Vector2 pos;

    int mass;
    float radius;

    Vector2 vel;
};

#endif