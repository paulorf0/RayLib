#include "engine.h"

Engine::Engine(int amount, int screen_height, int screen_width)
: screen_height(screen_height)
, screen_width(screen_width)
{
    int radius = 15;

    for(int i = 0; i < amount; i ++){
        int x = getRandomInt(radius + 10, screen_width - radius - 10); 
        int y = getRandomInt(radius + 10, screen_height - radius - 10); 
        
        std::cout << "RANDOM INTS: " << x << " " << y << std::endl;

        Ball ball(x, y);
        objects.push_back(ball);
    
        kinectEnergySystem += ball.getKinectEnergy();
    }

    GRAVITY = {0.f, -9.8f};
    t = 0;
}

Engine::~Engine() {
    saveVelocityData();
}

void Engine::update()
{
    for(Ball& ball: objects)
        ball.update();

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
        Ball& ball_i = objects[i];
        
        for(size_t j = i+1; j < objects.size(); j++){
            Ball& ball_j = objects[j];
            
            Vector2 axis = Vector2Subtract(ball_i.getPos(), ball_j.getPos());
            float dist_sq = Vector2LengthSqr(axis); 
            float r1 = ball_i.getRadius();
            float r2 = ball_j.getRadius();
            float radii_sum = r1 + r2;
            
            if(dist_sq <= (radii_sum * radii_sum)){
                // ".calcKinectEnergy()" return the old energy.
                float old_energy_i = ball_i.getKinectEnergy();
                float old_energy_j = ball_j.getKinectEnergy();

                float old_vel_i = Vector2Length(ball_i.getVel());
                float old_vel_j = Vector2Length(ball_j.getVel());

                logCollisionVelocity(old_vel_i);
                logCollisionVelocity(old_vel_j);
                std::cout << "ENERGIA DO SISTEMA: " << kinectEnergySystem << std::endl;


                float distance = sqrtf(dist_sq);
                
                Vector2 normal = (distance > 0) ? Vector2Scale(axis, 1.0f / distance) : (Vector2){1, 0};
                float overlap = radii_sum - distance;

                Vector2 correction = Vector2Scale(normal, overlap / 2.0f);
                ball_i.setPos(Vector2Add(ball_i.getPos(), correction));
                ball_j.setPos(Vector2Subtract(ball_j.getPos(), correction));

                CollisionResult collR = computeVelocityAfterCollision(ball_i, ball_j);

                ball_i.setVel(collR.new_b1_vel);
                ball_j.setVel(collR.new_b2_vel);

                float vel_i_after = Vector2Length(ball_i.getVel());
                float vel_j_after = Vector2Length(ball_j.getVel());
                
                logCollisionVelocity(vel_i_after);
                logCollisionVelocity(vel_j_after);


                ball_i.calcKinectEnergy();
                ball_j.calcKinectEnergy();
                
                kinectEnergySystem = kinectEnergySystem - old_energy_i - old_energy_j 
                   + ball_i.getKinectEnergy() + ball_j.getKinectEnergy();
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

    Vector2 vel1 = b1.getVel();
    Vector2 vel2 = b2.getVel();

    float length_proj_1 = Vector2DotProduct(b1.getVel(), normal);
    float length_proj_2 = Vector2DotProduct(b2.getVel(), normal);

    Vector2 vel_normal_1 = Vector2Scale(normal, length_proj_1);
    Vector2 vel_tang_1 = Vector2Subtract(vel1, vel_normal_1);

    Vector2 vel_normal_2 = Vector2Scale(normal, length_proj_2);
    Vector2 vel_tang_2 = Vector2Subtract(vel2, vel_normal_2);

    Vector2 new_vel_normal_1 = vel_normal_2;
    Vector2 new_vel_normal_2 = vel_normal_1;

    Vector2 final_vel_1 = Vector2Add(new_vel_normal_1, vel_tang_1);
    Vector2 final_vel_2 = Vector2Add(new_vel_normal_2, vel_tang_2);

    return {final_vel_1, final_vel_2};
}


void Engine::logCollisionVelocity(float velocity) {
    collisionVelocities.push_back(velocity);
}

void Engine::saveVelocityData() {
    std::ofstream file(velocityLogFile);
    if (file.is_open()) {
        file << "velocity\n"; // Cabeçalho
        for (float v : collisionVelocities) {
            file << v << "\n";
        }
        file.close();
        std::cout << "Dados de velocidade salvos em: " << velocityLogFile << std::endl;
    }
}