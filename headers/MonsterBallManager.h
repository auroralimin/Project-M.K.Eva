#pragma once

#include "Ball.h"
#include "Timer.h"
#include <vector>

class MonsterBallManager : public GameObject {
	public:
		MonsterBallManager(int n, GameObject *focus);
		~MonsterBallManager();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		enum BallManagerState {RESTING, WARNING, ATTACKING};

        GameObject *focus;
		BallManagerState state;
		std::vector<Ball> ballArray;
		Timer timer;

		void SwitchSprite(int sprite);
		void RandTeleport();
		bool b;
};
