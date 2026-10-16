#include "include/particle.hpp"
#include "include/vec2.hpp"
#include "raylib.h"
#include <cmath>
#include <vector>
#include <algorithm>
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
        if(std::abs(velocity_y)<minimum_velocity){
            p.position.y=p.previous_position.y;
        }
        else{
        float velocity_y=p.position.y-p.previous_position.y;
        p.position.y=screen_height-p.radius;
        p.previous_position.y=p.position.y+velocity_y*restitution;
        }
    }
    //Handle  collision with the ceiling
    if (p.position.y<p.radius){
        float velocity_y=p.position.y-p.previous_position.y;
        if(std::abs(velocity_y)<minimum_velocity){
            p.position.y=p.previous_position.y;
        }
        else{
        float velocity_y=p.position.y-p.previous_position.y;
        p.position.y=p.radius;
        p.previous_position.y=p.position.y+velocity_y*restitution;
        }}
    //Handle collision with the left wall
    if (p.position.x<p.radius){
        float velocity_x=p.position.x-p.previous_position.x;
        if(std::abs(velocity_x)<minimum_velocity){
            p.position.x=p.previous_position.x;
        }
        else{
        float velocity_x=p.position.x-p.previous_position.x;
        p.position.x=p.radius;
        p.previous_position.x=p.position.x+velocity_x*restitution;
        }
    }
    // Handle collision with the right wall
        if (p.position.x>screen_width-p.radius){
        float velocity_x=p.position.x-p.previous_position.x;
        if(std::abs(velocity_x)<minimum_velocity){
            p.position.x=p.previous_position.x;
        }
        else{
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
    for(auto& p:particles){
        apply_gravity(p,gravity,dt);
        apply_collision_with_boundary(p, screen_width, screen_height, restitution, minimum_velocity);
        apply_friction(p,friction_coefficient);
    }
   // Render
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10,10);
    for(auto& p:particles){
    DrawCircle(
        static_cast<int>(p.position.x),
        static_cast<int>(p.position.y),
        p.radius,
        RED
    );}
    EndDrawing();
  }
  CloseWindow();
    return 0;
}