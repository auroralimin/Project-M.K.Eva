#pragma once
#include <vector>
#include <memory>

#include "Sprite.h"
#include "GameObject.h"

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
		std::vector<std::unique_ptr<GameObject>> objectArray;
		//std::vector<GameObject*> objectArray;

		void input(void);
		void addObject(int mouseX, int mouseY);
};

