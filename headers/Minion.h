#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Bullet.h"

class Minion : public GameObject
{
	public:
		Minion(GameObject *minionCenter, float arcOffSet = 0);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void Shoot(Vec2 pos);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);

	private:
		GameObject *center;
		Sprite sp;
		float arc;
};

