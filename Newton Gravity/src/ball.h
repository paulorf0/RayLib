
#pragma once
#ifndef BALL_H
#define BALL_H
 
#include <raylib.h>
#include <raymath.h>

class Ball
{
public:
    Ball(int radius, float mass, Vector2 pos, Vector2 vel);
    void update(float dt);
    void draw() const;


    void applyForce(Vector2 force);
    void resetForce();

    Vector2 getVel() const;
    Vector2 getPos() const;
    int getRadius() const;
    float getMass() const;


    void setVel(Vector2 vel);
    void setPos(Vector2 pos);
private:
    void integrate(float dt);


    Vector2 pos, vel, acc, forces;

    int radius;
    float mass;
};

#endif