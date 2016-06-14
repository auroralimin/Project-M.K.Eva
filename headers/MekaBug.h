#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class MekaBug : public GameObject
{
	public:
		MekaBug(Vec2 pos);
		~MekaBug();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);

	private:
		enum MekaBugState {RESTING, MOVING, ATTACKING};
		MekaBugState state;
		Timer restTimer;
		int currentSprite;
		Sprite sprites[2];
		Vec2 speed;
};
