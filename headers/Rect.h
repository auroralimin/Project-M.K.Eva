#pragma once
#include "Vec2.h"

class Rect
{
	public:
		Vec2 pos, dim;

		Rect(void);
		Rect(Vec2 pos, Vec2 dim);
		void SumWithVec2(Vec2 v);
		bool IsInside(Vec2 area);
		Vec2 GetCenter(void);
};

