#pragma once
#include "GameObject.h"
#include "Vec2.h"

class Camera
{
	public:
		static Vec2 pos;
		static Vec2 speed;

		static void Follow(GameObject *newFocus);
		static void Unfollow(void);
		static void Update(float dt, int mapWidth, int mapHeight);

	private:
		static GameObject *focus;
};
		
