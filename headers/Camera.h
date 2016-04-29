#pragma once
#include "GameObject.h"
#include "Vec2.h"

class Camera
{
	public:
		static Vec2 pos;
		static Vec2 speed;

		static void follow(GameObject *newFocus);
		static void unfollow(void);
		static void update(float dt, int mapWidth, int mapHeight);

	private:
		static GameObject *focus;
};
		
