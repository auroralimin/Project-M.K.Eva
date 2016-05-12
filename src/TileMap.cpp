#include "TileMap.h"

#define UNUSED_VAR (void)

TileMap::TileMap(std::string file, TileSet *tileSet) : tileSet(tileSet)
{
	Load(file);
}

void TileMap::Load(std::string file)
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

void TileMap::SetTileSet(TileSet *tileSet)
{
	this->tileSet = tileSet;
}

int TileMap::At(int x, int y, int z)
{
	int index = (z*mapWidth*mapHeight) + (mapWidth*y) + x;
	return tileMatrix.at(index);
}

void TileMap::Render(int cameraX, int cameraY)
{
	for (int i = 0; i < mapDepth; i++)
		RenderLayer(i, cameraX, cameraY);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();

	for (int j = 0; j < mapWidth; ++j)
		for (int i = 0; i < mapHeight; ++i)
			tileSet->Render(At(i, j, layer), (i*tileWidth)-cameraX, (j*tileHeight)-cameraY);
}

int TileMap::GetWidth(void)
{
	return mapWidth;
}

int TileMap::GetHeight(void)
{
	return mapHeight;
}

int TileMap::GetDepth(void)
{
	return mapDepth;
}

