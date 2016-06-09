#pragma once

#include "GameObject.h"
#include "Sprite.h"

class Bullet : public GameObject
{
	private:
		Sprite sp;
		Vec2 speed;
		float distanceLeft;

	public:
		Bullet(Vec2 pos, float angle, float speed, float maxDistance, 
			std::string sprite, int frameCount = 1, float frameTime = 1,
			bool targetsPlayer = false);
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);

		bool targetsPlayer;
};
