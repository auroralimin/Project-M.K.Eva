#include "TileMap.h"
#include "Game.h"
#include "Vec2.h"
#include "Config.h"
#include <SDL2/SDL.h>

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
		std::cerr << "Failed to open file: " <<  file << std::endl;
		exit(EXIT_SUCCESS);	
	}

	fscanf(fp, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
	while(fscanf(fp, "%d,", &tile) != EOF)
		tileMatrix.emplace_back(tile);

	fclose(fp);

	LoadWallRects();
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

	for (int i = 0; i < mapWidth; ++i)
		for (int j = 0; j < mapHeight; ++j)
			tileSet->Render(At(i, j, layer), (i*tileWidth)-cameraX,
					(j*tileHeight)-cameraY);

	int color[4] = COLOR_HITBOX;
	if(Config::HITBOX_MODE && (layer == 1))
		for (auto hitbox : wallRect)
			hitbox.RenderFilledRect(color);
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

void TileMap::LoadWallRects(void)
{
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();

	for (int i = 1; i < mapWidth-1; i++)
	{
		int x = i*tileWidth, y = 2*tileHeight;
		if (At(i, y/tileHeight, 1) > -1)
			wallRect.emplace_back(Vec2(x, 2*tileHeight),
					Vec2(tileWidth, tileHeight));
		else if (At(i-1, y/tileHeight, 1) > -1)
			for (int j = -4; j < 0; j++)
				wallRect.emplace_back(Vec2(x-tileWidth, y + j*tileHeight),
						Vec2(tileWidth, tileHeight));
		else if (At(i+1, y/tileHeight, 1) > -1)
			for (int j = -4; j < 0; j++)
				wallRect.emplace_back(Vec2(x+tileWidth, y + j*tileHeight),
						Vec2(tileWidth, tileHeight));

		y = (mapHeight-1)*tileHeight;
		if (At(i, y/tileHeight, 1) > -1)
			wallRect.emplace_back(Vec2(x, (mapHeight-1)*tileHeight),
					Vec2(tileWidth, tileHeight));
		else if (At(i-1, y/tileHeight, 1) > -1)
			for (int j = 1; j < 4; j++)
				wallRect.emplace_back(Vec2(x-tileWidth, y + j*tileHeight),
						Vec2(tileWidth, tileHeight));
		else if (At(i+1, y/tileHeight, 1) > -1)
			for (int j = 1; j < 4; j++)
				wallRect.emplace_back(Vec2(x+tileWidth, y + j*tileHeight),
						Vec2(tileWidth, tileHeight));
	}

	for (int i = 3; i < mapHeight-1; i++)
	{
		int x = 0, y = i*tileHeight;
		if (At(x/tileWidth, y/tileHeight, 1) > -1)
			wallRect.emplace_back(Vec2(x, y),
					Vec2(tileWidth, tileHeight));
		else if (At(x/tileWidth, y/tileHeight-1, 1) > -1)
			for (int j = -4; j < 0; j++)
				wallRect.emplace_back(Vec2(x + j*tileWidth, y-tileHeight),
						Vec2(tileWidth, tileHeight));

		x = (mapWidth-1)*tileWidth;
		if (At(x/tileWidth, y/tileHeight, 1) > -1)
			wallRect.emplace_back(Vec2(x, y),
					Vec2(tileWidth, tileHeight));
		else if (At(x/tileWidth, y/tileHeight+1, 1) > -1)
			for (int j = 1; j < 4; j++)
				wallRect.emplace_back(Vec2(x + j*tileWidth, y-tileHeight),
						Vec2(tileWidth, tileHeight));
	}
}

std::vector<Rect> TileMap::GetWallRect(void)
{
	return wallRect;
}
