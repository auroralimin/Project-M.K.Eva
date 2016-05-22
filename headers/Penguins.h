#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Sound.h"

class Penguins : public GameObject
{
	public:
		Penguins(float x, float y);
		~Penguins(void);
		void Update(float dt);
		void Render(void);
		bool IsDead(void);
		void Shoot(void);
		void NotifyCollision(GameObject &other);
		bool Is(std::string className);
		void TakeDamage(int dmg = 1);

		Penguins *player;

	private:
		Sprite bodySp, cannonSp;
		Sound sound;
		Vec2 speed;
		float linearSpeed, cannonAngle;
};

