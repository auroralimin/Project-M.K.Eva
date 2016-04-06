#pragma once
#include "Sprite.h"
#include "GameObject.h"

class Face : public GameObject
{
	public:
		Face(int x, int y, float angle);
		~Face(void);
		void damage(int damage);
		void update(float dt);
		void render(void);
		bool isDead(void);

	private:
		int hitPoints;
		Sprite *sp;
		float angle;
};

