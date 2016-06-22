#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"
#include "Timer.h"

class TurretMob : public GameObject
{
	public:
		TurretMob(Vec2 pos, GameObject *focus);
		void Render(void);
		bool IsDead(void);
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
        enum TurretMobMovement {RESTING, MOVING, TRAPED};
		enum TurretMobState {IDLE, FRONT, FRONT_MIRROR, BACK, BACK_MIRROR};

        GameObject *focus;
        AnimationFSM animations;
		TurretMobMovement movementMode;
		Vec2 previousPos, destination;
        Timer restTimer;

        void LookAtFocus(void);
        void Movement(float dt);
        void Attack(float dt);
};

