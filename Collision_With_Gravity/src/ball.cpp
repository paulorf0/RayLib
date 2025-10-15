#include "ball.h"

Ball::Ball(float posx, float posy, int mass, int radius, Vector2 vel) 
: pos({posx,posy})  
, mass(mass)        
, vel(vel)
, radius(radius)     
{
    calcKinectEnergy();
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

Vector2 Ball::getPos()
{
    return pos;
}

void Ball::setPos(Vector2 newPos)
{
    this->pos = newPos;
}

Vector2 Ball::getVel(){
    return vel;
}

void Ball:: setVel(Vector2 newVel){
    this->vel = newVel;
}

void Ball::applyForce(Vector2 force)
{
    this->forces = Vector2Add(this->forces, force);
}

void Ball::resetForces()
{
    this->forces = {0, 0};
}

void Ball::integrate(float dt)
{
    accel = Vector2Scale(forces, 1.0f / mass);
    
    vel = Vector2Add(vel, Vector2Scale(accel, dt));
    pos = Vector2Add(pos, Vector2Scale(vel, dt));
    
    resetForces();
    calcKinectEnergy();
}

// Return old kinect energy
void Ball::calcKinectEnergy()
{
    kinectEnergy = mass * Vector2LengthSqr(vel) / 2;
}

float Ball::getKinectEnergy()
{
    return kinectEnergy;
}

int Ball::getMass()
{
    return mass;    
}

int Ball::getRadius()
{
    return radius;
}
