
#pragma once
#ifndef BALL_H
#define BALL_H
 
#include <raylib.h>
#include <raymath.h>

class Ball
{
public:
    Ball(float posx, float posy, int mass, int radius, Vector2 vel);
    void update(float dt);
    void draw() const;

    Vector2 getPos();
    void setPos(Vector2 newPos);

    Vector2 getVel();
    void setVel(Vector2 vel);    

    void applyForce(Vector2 force);
    void resetForces();        
    void integrate(float dt);

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
    Vector2 accel;
    Vector2 forces;

};

#endif