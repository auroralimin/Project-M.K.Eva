#pragma once
#include "Vec2.h"

class Rect
{
	public:
		Vec2 pos, dim;

		Rect(void);
		Rect(Vec2 pos, Vec2 dim);
		void sumWithVec2(Vec2 v);
		bool isInside(Vec2 area);
		void rotate(Vec2 pos, float angle);
};

