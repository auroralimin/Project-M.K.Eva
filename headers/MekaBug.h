#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class MekaBug : public GameObject
{
	public:
		MekaBug(Vec2 pos, GameObject *focus);
		~MekaBug();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		enum MekaBugState {RESTING, MOVING};

        GameObject *focus;
		MekaBugState state;
		Timer restTimer;
        Timer stuckTimer;
		int currentSprite;
		Sprite sprites[2];
		Vec2 speed;
		Vec2 previousPos;
        bool stuck;
};
