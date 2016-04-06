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

