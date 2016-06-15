#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Ball : public GameObject
{
	public:
		Ball(Vec2 pos);
		~Ball();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);
		bool IsInsideWall();

	private:
		enum BallState {RESTING, MOVING, WARNING, TELEPORTING};
		BallState state;
		Timer restTimer;
		Timer warningTimer;
		Timer attackTimer;
		int currentSprite;
		Sprite sprites[3];
		Vec2 speed;
		Vec2 previousPos;
		bool attackFinished;
};
