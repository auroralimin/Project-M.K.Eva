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

float Vec2::getModule(void)
{
	return std::sqrt((x*x) + (y*y));
}

Vec2 Vec2::normalize(void)
{
	float module = getModule();
	return Vec2(x/module, y/module);
}

float Vec2::distanceFromPoint(Vec2 p)
{
	return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
}

Vec2 Vec2::rotate(float angle)
{
	float c = std::cos(angle), s = std::sin(angle);
	return Vec2(x*c - y*s, y*c + x*s);
}

float Vec2::mag(void)
{
	return std::sqrt(x*x + y*y);
}

Vec2 Vec2::norm(void)
{
	return Vec2(x, y) * (1.f / this->mag());
}

float Vec2::dot(Vec2 p)
{
	return x*p.x + y*p.y;
}

