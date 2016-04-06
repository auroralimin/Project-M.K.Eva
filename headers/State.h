#pragma once
#include <iostream>
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
		//Eu tive problemas de compilacao com unique_ptr, como se ele tivesse sido deletado 
		//std::vector<std::unique_ptr<GameObject>> objectArray;
		std::vector<GameObject*> objectArray;

		void input(void);
		void addObject(int mouseX, int mouseY);
};

