#include "Rect.h"
#include <iostream>
#include <math.h>

Rect::Rect(void)
{
	pos.x = pos.y = dim.x = dim.y = 0.0;
}

Rect::Rect(Vec2 pos, Vec2 dim) : pos(pos), dim(dim) {}

void Rect::sumWithVec2(Vec2 v)
{
	pos += v;
}

bool Rect::isInside(Vec2 area)
{
	if ((pos.x <= area.x) && (pos.x > area.x - dim.x) &&
		(pos.y <= area.y) && (pos.y > area.y - dim.y))
		return true;
	return false;
}

void Rect::rotate(Vec2 pos, float angle)
{
	this->pos.x += (int)(pos.x*cos(angle) - pos.y*sin(angle));
	this->pos.y += (int)(pos.y*cos(angle) + pos.x*sin(angle));
}

