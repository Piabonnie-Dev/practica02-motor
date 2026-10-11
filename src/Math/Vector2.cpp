#include "Math/Vector2.hpp"
#include <algorithm>
#include <cmath>

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2 &v) const {
    return {x + v.x, y + v.y};
}

Vector2 Vector2::operator-(const Vector2 &v) const {
    return {x - v.x, y - v.y};
}
Vector2 Vector2::operator*(float n) const {
    return {x *n, y * n};
}

float Vector2::length_squared() const {
    return x*x+y*y;
}

float Vector2::length() const{
    return std::sqrt(length_squared());
}

Vector2 Vector2::normalized() const {
    float l = length();
    return l > 0.0001f ? Vector2{x/1, y/1} : Vector2{};
}

Vector2 Vector2::clamp(const Vector2 &min, const Vector2 &max) const {

    return {
        std::clamp(x, min.x, max.x),
        std::clamp(y, min.y, max.y)
    };
}