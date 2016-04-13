#pragma once
#include "Sprite.h"

class TileSet
{
	public:
		TileSet(int tileWidth, int tileHeight, std::string file);
		void render(int index, float x, float y);
		int getTileWidth(void);
		int getTileHeight(void);

	private:
		Sprite tileSet;
		int tileWidth, tileHeight;
		int rows, cols;
};

