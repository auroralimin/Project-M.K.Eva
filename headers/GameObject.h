#pragma once
#include <iostream>
#include "Rect.h"

class GameObject
{
	public:
		Rect box;
		float rotation;
		std::string animationImg;
		int frameCount;

		virtual ~GameObject(void) {};
		virtual void render(void) = 0;
		virtual bool isDead(void) = 0;
		virtual void update(float dt) = 0;
		virtual void notifyCollision(GameObject &other) = 0;
		virtual bool is(std::string className) = 0;
		virtual void takeDamage(int dmg = 1) = 0;

	protected:
		int hp;
};

