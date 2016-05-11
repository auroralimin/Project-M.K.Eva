#include "Vec2.h"
#include <math.h>

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
	return sqrt((x*x) + (y*y));
}

void Vec2::normalize(void)
{
	float module = getModule();
	x = x/module;
	y = y/module;
}

float Vec2::distanceFromPoint(Vec2 p)
{
	return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}

Vec2 Vec2::rotate(float angle)
{
	float c = cos(angle), s = sin(angle);
	return Vec2(x*c + y*s, y*c + x*s);
}

