#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

/*****************************************
 * The representation of the turret enemy
 ****************************************/

class Turret : public GameObject 
{
	public:
		Turret(Vec2 pos);
		~Turret();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);
		void ShootPattern1();
		void ShootPattern2();

	private:
		Sprite sp;
		Timer timer;
};
