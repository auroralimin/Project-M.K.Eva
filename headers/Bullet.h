#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Bullet : public GameObject
{
	public:
		Bullet(Vec2 pos, float angle, float speed, float maxDistance, std::string sprite,
				bool targetsPlayer = false, int frameCount = 3, float frameTime = 1.0);
		
		void update(float dt);
		void render(void);
		bool isDead(void);
		void notifyCollision(GameObject &other);
		bool is(std::string className);
		bool isTargetingPlayer(void);
		void takeDamage(int dmg = 1);

	private:
		bool targetsPlayer;
		Sprite sp;
		float distanceLeft;
		bool moving;
		Vec2 speed, finalPos;

		void killBullet(void);
};

