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
		void notifyCollision(GameObject &other);
		bool is(std::string className);
		void takeDamage(int dmg = 1);

	private:
		GameObject *center;
		Sprite sp;
		float arc;
};

