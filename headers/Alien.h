#pragma once
#include <vector>
#include <queue>
#include <memory>

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Minion.h"
#include "Timer.h"

class Alien : public GameObject
{
	public:
		static int alienCount;

		Alien(GameObject *focus, float x, float y, int nMinions);
		~Alien(void);	
		void update(float dt);
		void render(void);
		bool isDead(void);
		void notifyCollision(GameObject &other);
		bool is(std::string className);
		void takeDamage(int dmg = 1);
	
	private:
		enum AlienState
		{
			MOVING,
			RESTING
		};
		
		GameObject *focus;
		Sprite sp;
		Vec2 speed, destination;
		std::vector<std::unique_ptr<Minion>> minionArray;
		AlienState state;
		Timer restTimer;

		void shoot(float dt);
		void move(float dt);
};

