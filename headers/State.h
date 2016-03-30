#pragma once
#include "Sprite.h"
#include <iostream>

class State
{
	public:
		State(void);
		~State(void);
		bool isQuitRequested(void);
		void update(float dt);
		void render(void);

	private:
		Sprite *bg;
		bool quitRequested;
};

