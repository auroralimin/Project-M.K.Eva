#pragma once
#include <vector>
#include <queue>
#include <memory>

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Minion.h"

class Alien : public GameObject
{
	public:
		Alien(float x, float y, int nMinions);
		void update(float dt);
		void render(void);
		bool isDead(void);
		void notifyCollision(GameObject &other);
		bool is(std::string className);
		void takeDamage(int dmg = 1);
	
	private:
		class Action
		{
			public:
				enum ActionType {
					MOVE, 
					SHOOT
				};

				Action(ActionType type, float x, float y);

				ActionType type;
				Vec2 pos;
		};

		Sprite sp;
		Vec2 speed, finalPos;
		bool moving;
		std::queue<Action> taskQueue;
		std::vector<std::unique_ptr<Minion>> minionArray;

		void getTaskFromInput(void);
		void handleFirstTaskfromQueue(void);
		void updateMovement(void);
};

