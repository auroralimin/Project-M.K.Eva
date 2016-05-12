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
		virtual void Render(void) = 0;
		virtual bool IsDead(void) = 0;
		virtual void Update(float dt) = 0;
		virtual void NotifyCollision(GameObject &other) = 0;
		virtual bool Is(std::string className) = 0;
		virtual void TakeDamage(int dmg = 1) = 0;

	protected:
		int hp;
};

