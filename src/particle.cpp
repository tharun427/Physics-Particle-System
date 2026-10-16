#include "particle.hpp"

particle particle::update(float dt) {
    vec2 velocity = position - previous_position;
    previous_position = position;
    position = position + velocity + acceleration * (dt * dt);
    acceleration = {0.0f, 0.0f};
    return *this;
}