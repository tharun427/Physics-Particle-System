#pragma once

struct vec2
{
    float x;
    float y;

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(const vec2& other) const;
    vec2 operator*(float scalar) const;
    float operator&(const vec2& other) const;
    float magnitude() const;
};
