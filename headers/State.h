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
		bool IsQuitRequested(void);
		void Update(float dt);
		void Render(void);
		void AddObject(GameObject *ptr);

	private:
		Sprite bg;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		TileSet tileSet;
		TileMap tileMap;
};

