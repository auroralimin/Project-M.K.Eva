#pragma once
#include <vector>
#include "TileSet.h"

class TileMap
{
	public:
		TileMap(std::string file, TileSet *tileSet);
		void load(std::string file);
		void setTileSet(TileSet *tileSet);
		int at(int x, int y, int z = 1);
		void render(int cameraX = 0, int cameraY = 0);
		void renderLayer(int layer, int cameraX = 0, int cameraY = 0);
		int getWidth(void);
		int getHeight(void);
		int getDepth(void);

	private:
		TileSet *tileSet;
		std::vector<int> tileMatrix;
		int mapWidth, mapHeight, mapDepth;
};

