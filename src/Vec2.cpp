#include "Vec2.h"
#include <cmath>

Vec2::Vec2(void)
{
    x = y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vec2::GetModule(void)
{
    return std::sqrt((x * x) + (y * y));
}

Vec2 Vec2::Normalize(void)
{
    float module = GetModule();
    if (module == 0)
        return Vec2();
    return Vec2(x / module, y / module);
}

float Vec2::DistanceFromPoint(Vec2 p)
{
    return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
}

Vec2 Vec2::Rotate(float angle)
{
    float c = std::cos(angle), s = std::sin(angle);
    return Vec2(x * c - y * s, y * c + x * s);
}

float Vec2::Mag(void)
{
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Norm(void)
{
    return Vec2(x, y) * (1.f / this->Mag());
}

float Vec2::Dot(Vec2 p)
{
    return x * p.x + y * p.y;
}

