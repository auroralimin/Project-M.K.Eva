#pragma once
#include <vector>
#include <memory>

#include "Sprite.h"
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"

class State
{
	public:
		State(void);
		~State(void);
		bool isQuitRequested(void);
		void update(float dt);
		void render(void);

	private:
		Sprite bg;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		TileSet tileSet;
		TileMap tileMap;

		void input(void);
		void addObject(int mouseX, int mouseY);
};

