#pragma once
#include "State.h"
#include "Sprite.h"

class TitleState : public State
{
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);

	private:
		Sprite bg;
};

