#pragma once
#include <cmath>
#include "raylib.h"

// Overload operators for Vector2
struct Vector2 {
    float x, y;

    Vector2 operator-(const Vector2 &other) const {
        return {x - other.x, y - other.y};
    }
    Vector2 operator+(const Vector2 &other) const {
        return {x + other.x, y + other.y};
    }
    Vector2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }
    Vector2 operator/(float scalar) const {
        return {x / scalar, y / scalar};
    }
};

