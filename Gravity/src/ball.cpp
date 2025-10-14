#include "ball.h"

Ball::Ball(float posx, float posy) 
: pos({posx,posy})  
, mass(10)        
, radius(10)     
, vel({5,5})     
{
    calcKinectEnergy();
}

void Ball::update() 
{
    pos = Vector2Add(pos, vel);

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
