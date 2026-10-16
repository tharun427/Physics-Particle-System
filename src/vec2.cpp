#include "vec2.hpp"
#include <cmath>

vec2 vec2::operator+(const vec2& other) const
{
    return { x + other.x, y + other.y };
}

vec2 vec2::operator-(const vec2& other) const
{
    return { x - other.x, y - other.y };
}

vec2 vec2::operator*(const vec2& other) const
{
    return { x * other.x, y * other.y };
}

float vec2::operator&(const vec2& other) const
{
    return x * other.x + y * other.y;
}

float vec2::magnitude() const
{
    return std::sqrt(x * x + y * y);
}

vec2 vec2::operator*(float scalar) const{
    return {x*scalar,y*scalar};
}