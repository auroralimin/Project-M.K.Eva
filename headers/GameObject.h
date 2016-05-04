#pragma once
#include <iostream>
#include "Rect.h"

class GameObject
{
	public:
		Rect box;
		float rotation;

		virtual ~GameObject(void) {};
		virtual void render(void) = 0;
		virtual bool isDead(void) = 0;
		virtual void update(float dt) = 0;
};

