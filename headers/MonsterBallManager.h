#pragma once

#include <vector>

#include "Ball.h"
#include "Timer.h"

class MonsterBallManager : public GameObject {
	public:
		MonsterBallManager(GameObject *focus);
        Ball** AddBall(void);
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		enum BallsState {RESTING, WARNING, ATTACKING};

        GameObject *focus;
		unsigned int currentState;
		std::vector<Ball*> ballArray;
		Timer timer;

		void SetCurrentState(int state);
		void RandTeleport();
};

