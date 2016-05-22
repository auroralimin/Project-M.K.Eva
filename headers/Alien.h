#pragma once
#include <vector>
#include <queue>
#include <memory>

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Minion.h"
#include "Timer.h"
#include "Sound.h"

class Alien : public GameObject
{
	public:
		static int alienCount;

		Alien(GameObject *focus, float x, float y, int nMinions);
		~Alien(void);	
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);
	
	private:
		enum AlienState
		{
			MOVING,
			RESTING
		};
		
		GameObject *focus;
		Sprite sp;
		Sound sound;
		Vec2 speed, destination;
		std::vector<std::unique_ptr<Minion>> minionArray;
		AlienState state;
		Timer restTimer;

		void Shoot(float dt);
		void Move(float dt);
};

