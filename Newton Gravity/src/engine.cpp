#include "engine.h"

Engine::Engine(int amount)
{
    
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    while(amount--  > 0){
        int gap = 15;
        
        int mass = getRandomInt(30, 60);
        int radius = mass * 0.3;

        int x = getRandomInt(0 + radius + gap, screenWidth - radius - gap);
        int y = getRandomInt(0 + radius + gap, screenHeight - radius - gap);
        
        int velx = getRandomInt(-30, 30);
        int vely = getRandomInt(-30, 30);

        Ball ball(radius, mass, {x, y}, {velx, vely});
        balls.push_back(ball);
    }
}

Engine::Engine(std::vector<Ball> balls)
: balls(balls)
{
}

void Engine::update()
{
    for(size_t i = 0; i < balls.size(); i ++){
        Ball& b1 = balls[i];
        
        // COLLISION
        for(size_t j = i+1; j < balls.size(); j++){
            Ball& b2 = balls[j];
            
            Vector2 axis = Vector2Subtract(b1.getPos(), b2.getPos());
            float dist_sq = Vector2LengthSqr(axis);
            
            if (isnan(dist_sq) || dist_sq < 0.0001f) {
                continue;
            }

            float distance = sqrtf(dist_sq);
            Vector2 normal = (distance > 0.0001f) ? Vector2Scale(axis, 1.0f / distance) : (Vector2){1, 0};

            float r1 = b1.getRadius();
            float r2 = b2.getRadius();
            float radii_sum = r1 + r2;

            if(dist_sq <= (radii_sum * radii_sum)){
                
                float overlap = radii_sum - distance;

                Vector2 correction = Vector2Scale(normal, overlap / 2.0f);
                b1.setPos(Vector2Add(b1.getPos(), correction));
                b2.setPos(Vector2Subtract(b2.getPos(), correction));

                CollisionResult collR = computeVelocityAfterCollision(b1, b2);

                b1.setVel(collR.new_b1_vel);
                b2.setVel(collR.new_b2_vel);
            }
            else{
                // GRAVITATIONAL FORCE 
                float softening_factor = 100.0f;  
                float max_force = 1000.0f;       

                float m1_dot_m2 = b1.getMass() * b2.getMass();
                
                if (dist_sq < 0.0001f) {
                    dist_sq = 0.0001f;
                }
                
                float scalar_force = G * m1_dot_m2 / (dist_sq + softening_factor);
                
                if (scalar_force > max_force){
                    scalar_force = max_force;
                }
                if (isnan(scalar_force)) {
                    scalar_force = 0;
                }

                Vector2 F = Vector2Scale(normal, scalar_force);
                Vector2 minus_F = Vector2Negate(F);  

                b2.applyForce(F);
                b1.applyForce(minus_F);
            }
        }
    }


    for(Ball& ball : balls){
        float dt = GetFrameTime();

        ball.update(dt);
    }

}

void Engine::draw()
{
    for(Ball& ball : balls){
        ball.draw();
    }
}


CollisionResult Engine::computeVelocityAfterCollision(const Ball& b1, const Ball& b2)
{
    Vector2 pos_diff = Vector2Subtract(b1.getPos(), b2.getPos());
    float dist_sq = Vector2LengthSqr(pos_diff);

    if (dist_sq < 0.0001f) {
        return {b1.getVel(), b2.getVel()};
    }
    
    Vector2 normal = Vector2Normalize(pos_diff);
    Vector2 tangent = {-normal.y, normal.x};
    Vector2 vel1 = b1.getVel();
    Vector2 vel2 = b2.getVel();

    float v1n_scalar = Vector2DotProduct(vel1, normal);
    float v1t_scalar = Vector2DotProduct(vel1, tangent);
    float v2n_scalar = Vector2DotProduct(vel2, normal);
    float v2t_scalar = Vector2DotProduct(vel2, tangent);
    
    float m1 = b1.getMass();
    float m2 = b2.getMass();

    if (m1 < 0.0001f || m2 < 0.0001f) {
        return {vel1, vel2};
    }

    float v1n_scalar_final = (v1n_scalar * (m1 - m2) + 2 * m2 * v2n_scalar) / (m1 + m2);
    float v2n_scalar_final = (v2n_scalar * (m2 - m1) + 2 * m1 * v1n_scalar) / (m1 + m2);

    Vector2 v1n_final_vec = Vector2Scale(normal, v1n_scalar_final);
    Vector2 v2n_final_vec = Vector2Scale(normal, v2n_scalar_final);
    
    Vector2 v1t_final_vec = Vector2Scale(tangent, v1t_scalar);
    Vector2 v2t_final_vec = Vector2Scale(tangent, v2t_scalar);

    Vector2 final_vel_1 = Vector2Add(v1n_final_vec, v1t_final_vec);
    Vector2 final_vel_2 = Vector2Add(v2n_final_vec, v2t_final_vec);

    if (isnan(final_vel_1.x) || isnan(final_vel_1.y)) {
        final_vel_1 = b1.getVel();
    }
    if (isnan(final_vel_2.x) || isnan(final_vel_2.y)) {
        final_vel_2 = b2.getVel();
    }

    return {final_vel_1, final_vel_2};
}


int Engine::getRandomInt(int min, int max)
{
    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);
}
