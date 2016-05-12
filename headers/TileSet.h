#pragma once
#include "Sprite.h"

class TileSet
{
	public:
		TileSet(int tileWidth, int tileHeight, std::string file);
		void Render(int index, float x, float y);
		int GetTileWidth(void);
		int GetTileHeight(void);

	private:
		Sprite tileSet;
		int tileWidth, tileHeight;
		int rows, cols;
};

