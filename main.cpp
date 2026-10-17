#include "include/particle.hpp"
#include "include/vec2.hpp"
#include "raylib.h"
#include <cmath>
#include <vector>
#include <algorithm>
bool pause(){
    static bool pause_state=false;
if(IsKeyPressed(KEY_SPACE)){
    if(pause_state==false){
        pause_state=true;
    }
    else{
        pause_state=false;
    }}
   return pause_state;
}
void collision_between_particles(particle& p1, particle& p2,float restitution){
    float ratio1=p2.mass/(p1.mass+p2.mass);
    float ratio2=p1.mass/(p1.mass+p2.mass);
    vec2 delta=p2.position-p1.position;
    float distance=delta.magnitude();
    float overlap=p1.radius+p2.radius-distance;
    if(overlap>0.0f){
        vec2 normal=delta*(1.0f/distance);
        p1.position=p1.position-normal*overlap*ratio1;
        p2.position=p2.position+normal*overlap*ratio2;
    }
}
void add_particle(std::vector<particle>& particles,float dt)
{    static float timer=0.0f;
    timer+=dt;
    static particle p;
    static bool is_charging=false;
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && is_charging==false){
        p.position={static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY())};
        p.previous_position=p.position;
        p.acceleration={0.0f,0.0f};
        is_charging=true;
        p.color={static_cast<unsigned char>(GetRandomValue(50,255)),static_cast<unsigned char>(GetRandomValue(50,255)),static_cast<unsigned char>(GetRandomValue(50,255)),255};
    }
if(is_charging==true && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
    p.previous_position={static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY())};
    is_charging=false;
    p.mass=timer*100.0f;
    p.radius=std::sqrt(p.mass);
    particles.push_back(p);
    timer=0.0f;
}}
void apply_gravity(particle& p, const vec2& gravity, float dt) {
    p.acceleration = p.acceleration + gravity;
    p.update(dt);
}
void apply_friction(particle& p, float friction_coefficient){
     //Friction
    if (p.position.y==p.previous_position.y){
        float velocity_x=p.position.x-p.previous_position.x;
        p.previous_position.x=p.position.x-velocity_x*friction_coefficient;
    
}
}
void apply_collision_with_boundary(particle& p, int screen_width, int screen_height,float restitution,float minimum_velocity){
 // Handle collision with the floor
    if (p.position.y>screen_height-p.radius){
        float velocity_y=p.position.y-p.previous_position.y;
        float penetration=screen_height-p.radius-p.position.y;
        if(std::abs(velocity_y)<minimum_velocity){
            p.position.y=p.previous_position.y;
        }
        else{
        p.previous_position.y-=penetration;
        float velocity_y=p.position.y-p.previous_position.y;
        p.position.y=screen_height-p.radius;
        p.previous_position.y=p.position.y+velocity_y*restitution;
        }
    }
    //Handle  collision with the ceiling
    if (p.position.y<p.radius){
        float velocity_y=p.position.y-p.previous_position.y;
        float penetration=p.radius-p.position.y;
        if(std::abs(velocity_y)<minimum_velocity){
            p.position.y=p.previous_position.y;
        }
        else{
        p.previous_position.y+=penetration;
        float velocity_y=p.position.y-p.previous_position.y;
        p.position.y=p.radius;
        p.previous_position.y=p.position.y+velocity_y*restitution;
        }}
    //Handle collision with the left wall
    if (p.position.x<p.radius){
        float penetration=p.radius-p.position.x;
        float velocity_x=p.position.x-p.previous_position.x;
        if(std::abs(velocity_x)<minimum_velocity){
            p.position.x=p.previous_position.x;
        }
        else{
        p.previous_position.x+=penetration;
        float velocity_x=p.position.x-p.previous_position.x;
        p.position.x=p.radius;
        p.previous_position.x=p.position.x+velocity_x*restitution;
        }
    }
    // Handle collision with the right wall
        if (p.position.x>screen_width-p.radius){
        float velocity_x=p.position.x-p.previous_position.x;
        float penetration=screen_width-p.radius-p.position.x;
        if(std::abs(velocity_x)<minimum_velocity){
            p.position.x=p.previous_position.x;
        }
        else{
        p.previous_position.x-=penetration;
        float velocity_x=p.position.x-p.previous_position.x;
        p.position.x=screen_width-p.radius;
        p.previous_position.x=p.position.x+velocity_x*restitution;
        }}
}
int main(){
int screen_height=400;
int screen_width=800;
float friction_coefficient=0.985f;
float minimum_velocity=1.0f;
float restitution=0.8f;
  InitWindow(screen_width,screen_height,"Physics Particle Simulation");
  SetTargetFPS(60);
  std::vector<particle> particles;
  vec2 gravity={0.0f,981.0f};
  while(!WindowShouldClose()){
    float dt=GetFrameTime();
    add_particle(particles,dt);
    if(!pause()){
    for(auto& p:particles){
        apply_gravity(p,gravity,dt);
        apply_collision_with_boundary(p, screen_width, screen_height, restitution, minimum_velocity);
        apply_friction(p,friction_coefficient);
    }}
    for(size_t i=0;i<particles.size();i++){
        for(size_t j=i+1;j<particles.size();j++){
            collision_between_particles(particles[i],particles[j],restitution);
        }
    }
   // Render
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(10,10);
    for(auto& p:particles){
    DrawCircle(
        static_cast<int>(p.position.x),
        static_cast<int>(p.position.y),
        p.radius,
        p.color
    );}
    EndDrawing();
  }
  CloseWindow();
    return 0;
}