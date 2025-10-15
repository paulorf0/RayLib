#include "engine.h"

Engine::Engine(int amount, int screen_height, int screen_width)
{
    this->screen_width = screen_width;
    this->screen_height = screen_height; 





    randomBalls(amount);   
    // customBalls();
}

void Engine::update()
{
    float dt = GetFrameTime() * timeVelocity;

    for(Ball& ball: objects){
        ball.resetForces();

        ball.applyForce(Vector2Scale(GRAVITY, ball.getMass()));

        ball.update(dt);
    }
    collision();
}

void Engine::draw()
{
    for(Ball& ball: objects)
        ball.draw();
}

void Engine::collision()
{
    for(size_t i = 0; i < objects.size(); i ++){
        Ball& b1 = objects[i];
        
        for(size_t j = i+1; j < objects.size(); j++){
            Ball& b2 = objects[j];
            
            Vector2 axis = Vector2Subtract(b1.getPos(), b2.getPos());
            float dist_sq = Vector2LengthSqr(axis); 
            float r1 = b1.getRadius();
            float r2 = b2.getRadius();
            float radii_sum = r1 + r2;
            
            if(dist_sq <= (radii_sum * radii_sum)){
                // ".calcKinectEnergy()" return the old energy.
                float old_energy_i = b1.getKinectEnergy();
                float old_energy_j = b2.getKinectEnergy();
                std::cout << "ENERGIA DO SISTEMA: " << kinectEnergySystem << std::endl;


                float distance = sqrtf(dist_sq);
                
                Vector2 normal = (distance > 0) ? Vector2Scale(axis, 1.0f / distance) : (Vector2){1, 0};
                float overlap = radii_sum - distance;

                Vector2 correction = Vector2Scale(normal, overlap / 2.0f);
                b1.setPos(Vector2Add(b1.getPos(), correction));
                b2.setPos(Vector2Subtract(b2.getPos(), correction));

                CollisionResult collR = computeVelocityAfterCollision(b1, b2);



                b1.setVel(collR.new_b1_vel);
                b2.setVel(collR.new_b2_vel);

                b1.calcKinectEnergy();
                b2.calcKinectEnergy();
                
                kinectEnergySystem = kinectEnergySystem - old_energy_i - old_energy_j 
                   + b1.getKinectEnergy() + b2.getKinectEnergy();
            }
        }
    }
}

int Engine::getRandomInt(int min, int max)
{
    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(generator);}

// Velocity is conserved
CollisionResult Engine::computeVelocityAfterCollision(Ball b1, Ball b2)
{
    
    Vector2 normal = Vector2Normalize(Vector2Subtract(b1.getPos(), b2.getPos()));
    Vector2 tangent = {-normal.y, normal.x};

    Vector2 vel1 = b1.getVel();
    Vector2 vel2 = b2.getVel();

    float v1n_scalar = Vector2DotProduct(vel1, normal);
    float v1t_scalar = Vector2DotProduct(vel1, tangent);
    float v2n_scalar = Vector2DotProduct(vel2, normal);
    float v2t_scalar = Vector2DotProduct(vel2, tangent);
    
    float m1 = b1.getMass();
    float m2 = b2.getMass();

    float v1n_scalar_final = (v1n_scalar * (m1 - m2) + 2 * m2 * v2n_scalar) / (m1 + m2);
    float v2n_scalar_final = (v2n_scalar * (m2 - m1) + 2 * m1 * v1n_scalar) / (m1 + m2);

    Vector2 v1n_final_vec = Vector2Scale(normal, v1n_scalar_final);
    Vector2 v2n_final_vec = Vector2Scale(normal, v2n_scalar_final);
    
    Vector2 v1t_final_vec = Vector2Scale(tangent, v1t_scalar);
    Vector2 v2t_final_vec = Vector2Scale(tangent, v2t_scalar);

    Vector2 final_vel_1 = Vector2Add(v1n_final_vec, v1t_final_vec);
    Vector2 final_vel_2 = Vector2Add(v2n_final_vec, v2t_final_vec);

    return {final_vel_1, final_vel_2};
}

void Engine::randomBalls(int amount)
{
    int radius = 15;
    for(int i = 0; i < amount; i ++){
        int x = getRandomInt(radius + 10, screen_width - radius - 10); 
        int y = getRandomInt(radius + 10, screen_height - radius - 10); 
        
        int mass = getRandomInt(30, 60); 


        std::cout << "RANDOM INTS: " << x << " " << y << std::endl;

        Ball ball(x, y, mass, mass * 0.3f, {20, 0});
        objects.push_back(ball);
    
        kinectEnergySystem += ball.getKinectEnergy();
    }
}

void Engine::customBalls()
{
    int radius1 = 50;
    int radius2 = 20;

    int mass1 = 1000;
    int mass2 = 10;
    // Mass1 ->          <- Mass2
    Ball ball1(0 + radius1 + 150, screen_height - radius1, mass1, radius1, {-170, 0});
    Ball ball2(screen_width - radius2 - 400, screen_height - radius2 - radius1/2, mass2, radius2, {0, 0});

    objects.push_back(ball1);
    objects.push_back(ball2);
}
