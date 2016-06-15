#pragma once

#include "GameObject.h"
#include "Sprite.h"

class Ball : public GameObject
{
	public:
		Ball(Vec2 pos);
		~Ball();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);
		bool IsInsideWall();
		void SetCurrentSprite(int state);

	private:
		int currentSprite;
		Sprite sprites[3];
		Vec2 previousPos;
};
