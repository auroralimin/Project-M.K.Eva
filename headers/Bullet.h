#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Bullet : public GameObject
{
	public:
		Bullet(Vec2 pos, float angle, float speed, float maxDistance, std::string sprite);
		void update(float dt);
		void render(void);
		bool isDead(void);

	private:
		Sprite sp;
		float distanceLeft;
		bool moving;
		Vec2 speed, finalPos;
};

