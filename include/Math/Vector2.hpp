#pragma once

struct Vector2 {
    float x{0};
    float y{0};

    Vector2() = default;
    Vector2(float x, float y);

    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2 operator*(float n) const;

    float length_squared() const;
    float length() const;
    Vector2 normalized() const;
    Vector2 clamp(const Vector2 &min, const Vector2 &max) const;
};