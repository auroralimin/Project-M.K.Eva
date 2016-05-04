#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Bullet.h"

class Minion : public GameObject
{
	public:
		Minion(GameObject *minionCenter, float arcOffSet = 0);
		void update(float dt);
		void render(void);
		bool isDead(void);
		void shoot(Vec2 pos);

	private:
		GameObject *center;
		Sprite sp;
		float arc;
};

