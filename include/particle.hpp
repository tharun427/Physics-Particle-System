#pragma once
#include "vec2.hpp"
#include "raylib.h"

struct particle{
    vec2 position;
    vec2 previous_position;
    vec2 acceleration;
    float mass;
    float radius;
    Color color;

    particle update(float dt);
};