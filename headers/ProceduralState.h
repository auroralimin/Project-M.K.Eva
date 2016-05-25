#pragma once

#include "State.h"
#include "LevelMap.h"

class ProceduralState : public State
{
	public:
		ProceduralState(void);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);
		bool IsCollidingWithWall(GameObject* obj);
	private:
		unsigned int seed;
};

