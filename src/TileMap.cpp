#include "TileMap.h"

#define UNUSED_VAR (void)

TileMap::TileMap(std::string file, TileSet *tileSet) : tileSet(tileSet)
{
	load(file);
}

void TileMap::load(std::string file)
{
	int tile;
	FILE *fp = fopen(file.c_str(), "r");

	if (!fp)
	{
		std::cerr << "Failed to create a renderer: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);	
	}

	fscanf(fp, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
	while(fscanf(fp, "%d,", &tile) != EOF)
		tileMatrix.emplace_back(tile);

	fclose(fp);
}

void TileMap::setTileSet(TileSet *tileSet)
{
	this->tileSet = tileSet;
}

int TileMap::at(int x, int y, int z)
{
	int index = (z*mapWidth*mapHeight) + (mapWidth*y) + x;
	return tileMatrix.at(index);
}

void TileMap::render(int cameraX, int cameraY)
{
	for (int i = 0; i < mapDepth; i++)
		renderLayer(i, cameraX, cameraY);
}

void TileMap::renderLayer(int layer, int cameraX, int cameraY)
{
	int tileWidth = tileSet->getTileWidth();
	int tileHeight = tileSet->getTileHeight();

	for (int j = 0; j < mapWidth; ++j)
		for (int i = 0; i < mapHeight; ++i)
			tileSet->render(at(i, j, layer), (i*tileWidth)-cameraX, (j*tileHeight)-cameraY);
}

int TileMap::getWidth(void)
{
	return mapWidth;
}

int TileMap::getHeight(void)
{
	return mapHeight;
}

int TileMap::getDepth(void)
{
	return mapDepth;
}

