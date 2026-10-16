#include "particle.hpp"

particle particle::update(float dt) {
    vec2 velocity = position - previous_position;
    previous_position = position;
    position = position + velocity*0.999f + acceleration * (dt * dt);   // Added air drag factor of 0.999 to velocity
    acceleration = {0.0f, 0.0f};
    return *this;
}