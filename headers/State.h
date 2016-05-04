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
		void addObject(GameObject *ptr);

	private:
		Sprite bg;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		TileSet tileSet;
		TileMap tileMap;
};

