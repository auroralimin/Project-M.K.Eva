#pragma once
#include "Sprite.h"
#include "GameObject.h"

class Face : public GameObject
{
	public:
		Face(int x, int y, float angle);
		void damage(int damage);
		void update(float dt);
		void render(void);
		bool isDead(void);

	private:
		Sprite sp;
		int hitPoints;
		float angle;
};

