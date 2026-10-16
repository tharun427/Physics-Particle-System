#pragma once
#include "vec2.hpp"

struct particle{
    vec2 position;
    vec2 previous_position;
    vec2 acceleration;
    float mass;
    float radius;

    particle update(float dt);
};