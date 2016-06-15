#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class MekaBug : public GameObject
{
	public:
		MekaBug(Vec2 pos);
		~MekaBug();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		enum MekaBugState {RESTING, MOVING};
		MekaBugState state;
		Timer restTimer;
		int currentSprite;
		Sprite sprites[2];
		Vec2 speed;
		Vec2 previousPos;
};
