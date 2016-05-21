#pragma once
#include "State.h"
#include "Sprite.h"
#include "TileSet.h"
#include "TileMap.h"

class StageState : public State
{
	public:
		StageState(void);
		~StageState(void);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);

	protected:
		void UpdateArray(float dt);

	private:
		Sprite bg;
		TileSet tileSet;
		TileMap tileMap;
};

