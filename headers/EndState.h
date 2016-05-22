#pragma once
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "Timer.h"
#include "StateData.h"

class EndState : public State
{
	public:
		EndState(StateData data);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);

	private:
		Sprite bg;
		Music music;
		Text text1, text2;
		Timer timer;
};

