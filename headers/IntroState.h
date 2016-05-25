#pragma once

#include "State.h"
#include "LevelMap.h"
#include "GameObject.h"

class IntroState : public State
{
	public:
		IntroState(void);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);
		bool IsCollidingWithWall(GameObject* o);
	private:
		LevelMap map;
};

