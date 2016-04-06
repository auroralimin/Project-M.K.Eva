#pragma once
#include <iostream>
#include "Vec2.h"

class Rect
{
	public:
		int x, y;
		int w, h;

		Rect(void);
		Rect(int x, int y, int w, int h);
		void sumWithVec2(Vec2 v);
		bool isInside(int x, int y);
};

