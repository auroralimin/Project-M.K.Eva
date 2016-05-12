#include "Rect.h"
#include <iostream>
#include <cmath>

Rect::Rect(void)
{
	pos.x = pos.y = dim.x = dim.y = 0.0;
}

Rect::Rect(Vec2 pos, Vec2 dim) : pos(pos), dim(dim) {}

void Rect::SumWithVec2(Vec2 v)
{
	pos += v;
}

bool Rect::IsInside(Vec2 area)
{
	if ((pos.x <= area.x) && (pos.x > area.x - dim.x) &&
		(pos.y <= area.y) && (pos.y > area.y - dim.y))
		return true;
	return false;
}

Vec2 Rect::GetCenter(void)
{
	return pos + dim/2;
}

