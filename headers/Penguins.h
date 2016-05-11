#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Penguins : public GameObject
{
	public:
		Penguins(float x, float y);
		~Penguins(void);
		void update(float dt);
		void render(void);
		bool isDead(void);
		void shoot(void);

		Penguins *player;

	private:
		Sprite bodySp, cannonSp;
		Vec2 speed;
		int hp;
		float linearSpeed, cannonAngle;
};

