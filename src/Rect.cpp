#include "Rect.h"
#include <iostream>
#include <math.h>

Rect::Rect(void)
{
	x = y = w = h = 0.0;
}

Rect::Rect(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;

	this->w = w;
	this->h = h;
}

void Rect::sumWithVec2(Vec2 v)
{
	x = v.x;
	y = v.y;
}

bool Rect::isInside(int x, int y)
{
	if ((this->x <= x) && (this->x > x - w) &&
		(this->y <= y) && (this->y > y - h))
		return true;
	return false;
}

void Rect::rotate(int x, int y, float angle)
{
	this->x += (int)(x*cos(angle) - y*sin(angle));
	this->y += (int)(y*cos(angle) + x*sin(angle));
}

