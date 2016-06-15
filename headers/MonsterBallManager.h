#pragma once

#include "Ball.h"
#include <vector>

class MonsterBallManager : public GameObject {
	public:
		MonsterBallManager(int numBall);
		~MonsterBallManager();
		void Render();
		bool IsDead();
		void Update(float dt);
		void NotifyCollision(GameObject &other, bool movement);
		bool Is(std::string className);
		void TakeDamage(float dmg = 1);

	private:
		std::vector<Ball> ballArray;
};
