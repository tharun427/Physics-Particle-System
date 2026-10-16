#include "include/particle.hpp"
#include "include/vec2.hpp"
#include "raylib.h"
#include <cmath>

int main(){
int screen_height=400;
int screen_width=800;
float minimum_velocity=1.0f;
float restitution=0.8f;
  InitWindow(screen_width,screen_height,"Physics Particle Simulation");
  SetTargetFPS(60);
  
  particle p;
  p.position={400.0f,100.0f};
  p.previous_position={400.0f,100.0f};
  p.acceleration={0.0f,0.0f};
  vec2 gravity={0.0f,981.0f};
  p.mass=1.0f;
  p.radius=10.0f;
  while(!WindowShouldClose()){
    float dt=GetFrameTime();
    p=p.update(dt);
    p.acceleration=p.acceleration+gravity;
    p.update(dt);

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
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10,10);
    
    DrawCircle(
        static_cast<int>(p.position.x),
        static_cast<int>(p.position.y),
        p.radius,
        RED
    );
    EndDrawing();
  }
  CloseWindow();
    return 0;
}