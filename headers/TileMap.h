#pragma once
#include <vector>
#include "TileSet.h"

class TileMap
{
	public:
		TileMap(std::string file, TileSet *tileSet);
		void Load(std::string file);
		void SetTileSet(TileSet *tileSet);
		int At(int x, int y, int z = 1);
		void Render(int cameraX = 0, int cameraY = 0);
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
		int GetWidth(void);
		int GetHeight(void);
		int GetDepth(void);

	private:
		TileSet *tileSet;
		std::vector<int> tileMatrix;
		int mapWidth, mapHeight, mapDepth;
};

