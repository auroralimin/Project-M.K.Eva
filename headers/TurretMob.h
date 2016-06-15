#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class TurretMob : public GameObject
{
	public:
		TurretMob(Vec2 pos, GameObject *focus);
		~TurretMob();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		enum TurretMobState {RESTING, MOVING};

        GameObject *focus;
		TurretMobState state;
		Timer restTimer;
		Timer attackTimer;
		int currentSprite;
		Sprite sprites[5];
		Vec2 speed;
		Vec2 destination;
		Vec2 previousPos;
};
