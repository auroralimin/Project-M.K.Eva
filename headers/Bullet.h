#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Bullet : public GameObject
{
	public:
		Bullet(Vec2 pos, float angle, float speed, float maxDistance, std::string sprite,
				bool targetsPlayer = false, int frameCount = 3, float frameTime = 0.3);
		
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		bool IsTargetingPlayer(void);
		void TakeDamage(int dmg = 1);

	private:
		bool targetsPlayer;
		Sprite sp;
		float distanceLeft;
		bool moving;
		Vec2 speed, finalPos;

		void KillBullet(void);
};

