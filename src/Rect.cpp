#include "Rect.h"
#include <iostream>
#include <cmath>

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

Vec2 Rect::getCenter(void)
{
	return pos + dim/2;
}

void Rect::rotate(Vec2 pos, float angle)
{
	this->pos.x += (int)(pos.x*std::cos(angle) - pos.y*std::sin(angle));
	this->pos.y += (int)(pos.y*std::cos(angle) + pos.x*std::sin(angle));
}

