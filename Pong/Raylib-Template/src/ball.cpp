#include "ball.h"

Ball::Ball(double x_, double y_, double speedX_, double speedY_, int screenX_, int screenY_, int height_, int width_, int radius_)
{
    x = x_;
    y = y_;
    speedX = speedX_;
    speedY = speedY_;
    screenX = screenX_;
    screenY = screenY_;

    height = height_;
    width = width_;

    radius = radius_;
}

void Ball::Update(double p1Y, double p2Y)
{
    // Colisão bordas
    if (x + radius >= screenX - error || x - radius <= 0 + error)
        speedX *= -1;
    if (y + radius >= screenY - error || y - radius <= 0 + error)
        speedY *= -1;

       if (x - radius <= width + error &&
        y + radius >= p1Y && y - radius <= p1Y + height)
    {
        speedX *= -1;
        std::cout << "Colisão p1";
    }
    else if (x + radius >= screenX - width - error &&
             y + radius >= p2Y && y - radius <= p2Y + height)
    {
        std::cout << "Colisão p2";
        speedX *= -1;
    }

    x += speedX;
    y += speedY;
}

void Ball::Draw()
{
    DrawCircle(x, y, radius, WHITE);
}