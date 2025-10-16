#include "ball.h"


Ball::Ball(int radius, float mass, Vector2 pos, Vector2 vel)
: radius(radius)
, mass(mass)
, pos(pos)
, vel(vel)
{
}

void Ball::update(float dt)
{
    integrate(dt);

    float current_x = pos.x;
    float current_y = pos.y;

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if ((current_x + radius >= screenWidth) || (current_x - radius <= 0)) {
        if (current_x + radius >= screenWidth) { 
            float overlap = (current_x + radius) - screenWidth;
            pos.x -= overlap; 
        }
        if (current_x - radius <= 0) { 
            float overlap = 0 - (current_x - radius); 
            pos.x += overlap; 
        }
        
        vel.x *= -1;
    }

    if ((current_y + radius >= screenHeight) || (current_y - radius <= 0)) {
        if (current_y + radius >= screenHeight) {
            float overlap = (current_y + radius) - screenHeight;
            pos.y -= overlap;
        }
        if (current_y - radius <= 0) { 
            float overlap = 0 - (current_y - radius);
            pos.y += overlap; 
        }
        
        vel.y *= -1;
    }
}

void Ball::draw() const
{
    DrawCircleV(pos, radius, WHITE);
}

void Ball::applyForce(Vector2 force)
{
    this->forces = Vector2Add(force, this->forces); 
}

void Ball::resetForce()
{
    this->forces = {0,0};
}
 
Vector2 Ball::getVel() const
{
    return vel;
}

Vector2 Ball::getPos() const
{
    return pos;
}

int Ball::getRadius() const
{
    return radius;
}

float Ball::getMass() const
{
    return mass;
}

void Ball::setVel(Vector2 vel)
{
    this->vel = vel;
}

void Ball::setPos(Vector2 pos)
{
    this->pos = pos;
}

void Ball::integrate(float dt)
{
    if (isnan(forces.x) || isnan(forces.y)) {
        forces = {0, 0};
    }


    acc = Vector2Scale(forces, 1.0f / mass);
    
    if (isnan(acc.x) || isnan(acc.y)) {
        acc = {0, 0};
    }

    vel = Vector2Add(vel, Vector2Scale(acc, dt));
    pos = Vector2Add(pos, Vector2Scale(vel, dt));
    
    if (isnan(pos.x) || isnan(pos.y)) {
        pos = {400, 400}; 
    }
    if (isnan(vel.x) || isnan(vel.y)) {
        vel = {0, 0};
    }

    resetForce();
}