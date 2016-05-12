#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Timer.h"

class Animation : public GameObject
{
	public:
		Animation(Vec2 pos, float rotation, std::string sprite,
				int frameCount = 1, float frameTime = 0.1, bool ends = true);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);

	private:
		Sprite sp;
		Timer endTimer;
		float timeLimit;
		bool oneTimeOnly;
};

